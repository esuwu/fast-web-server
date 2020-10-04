#include "server.h"
#include <csignal>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include "../request/request.h"
#include <unistd.h>
using namespace std;
#define EPOLL_SIZE 128
Server& Server::Start(const string_view &address,
                      uint16_t port,
                      size_t max_connection,
                      size_t max_thread,
                      const string &doc_root) {
    static Server server(address, port, max_connection, max_thread, doc_root);
    return server;
}

Server & Server::GetInstance() {
    return Start("", 0, 0, 0, "");
}

Server::Server(const string_view &address,
               uint16_t port,
               size_t max_connection,
               size_t max_thread,
               const string &doc_root) : mSpmcQueue(max_connection){
    std::signal(SIGTERM, HandleSignal);
    std::signal(SIGABRT, HandleSignal);

    for(size_t i = 0; i < max_thread; i++) {
        mWorkers.emplace_back([this, doc_root] {this->Work(doc_root);});
    }
    try{
        Open(address, port);
        Listen(static_cast<int>(max_connection));
        CreateEpoll();
        AddEpoll(max_connection, EPOLLIN);
    }
    catch (std::string err) {
        cerr << err << endl;
        Close();
        throw;
    }
}

void Server::Close() {
    mSockFD.Close();
    mEpollFD.Close();
}

void Server::Listen(int maxConnect) {
    if (::listen(mSockFD, maxConnect) != 0) {
        throw "Failed to listen socket";
    }
}

bool Server::IsOpened() const {
    return mSockFD.IsOpened();
}

Server::~Server() {
    JoinWorkers();
}

void Server::Open(const string_view& address, uint16_t port) {
    if (IsOpened()) {
        Close();
    }
    mSockFD = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (mSockFD < 0) {
        throw "Cannot create socket";
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = ::htons(port);
    if (::inet_aton(address.data(), &serv_addr.sin_addr) == 0) {
        throw "Invalid ipb4 address";

    }
    if (::bind(mSockFD, reinterpret_cast<sockaddr*>(&serv_addr),
               sizeof(serv_addr)) != 0) {
        throw "Cannot bind socket";
    }
}

void Server::JoinWorkers() {
    if (mDone) {
        return;
    }
    mDone = true;
    mCV.notify_all();

    for(auto &worker : mWorkers) {
        worker.join();
    }
}

void Server::Run() {
   epoll_event events[EPOLL_SIZE];

   while(IsOpened()) {
       int fdCount = epoll_wait(mEpollFD, events, EPOLL_SIZE, -1);
       if (fdCount < 0) {
           if (errno == EINTR) {
               continue;
           }
           throw "Error in waiting epoll";
       }

       for(int i = 0; i < fdCount; i++) {
           int fd = events[i].data.fd;
           if (fd == mSockFD) {
               AcceptClients();
           } else {
               HandleClients(fd, events[i]);
           }
       }
   }

}

void Server::HandleSignal(int) {
    GetInstance().JoinWorkers();
    GetInstance().Close();
}

void Server::CreateEpoll() {
    mEpollFD = epoll_create(1);
    if (mEpollFD < 0) {
        throw "Cannot create epoll";
    }
}

void Server::AddEpoll(int FD, uint32_t events) const {
    epoll_event event{};
    event.data.fd = FD;
    event.events = events;
    if (epoll_ctl(mEpollFD, EPOLL_CTL_ADD, FD, &event) < 0 ) {
        throw "Cannot add file descriptor to epoll";
    }
}


void Server::AcceptClients() {
    while(true) {
        sockaddr_in client_addr{};
        socklen_t addr_size = sizeof(client_addr);

        int connFd = ::accept4(mSockFD, reinterpret_cast<sockaddr*>(&client_addr),
                                &addr_size, SOCK_NONBLOCK);
        if (connFd < 0) {
            if (errno == EINTR) {
                continue;
            }
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return;
            }
            throw "Cannot accept connection";
        }
        AddEpoll(connFd, EPOLLIN | EPOLLRDHUP | EPOLLET);
    }
}

void Server::HandleClients(int fd, epoll_event event) {
    if (event.events & EPOLLHUP || event.events & EPOLLERR || event.events & EPOLLRDHUP) {
        return;
    }
    mSpmcQueue.push(fd);
    mCV.notify_all();
}

void Server::Work(const string &doc_root) {
    std::mutex mtx;
    while(!mDone) {
        std::unique_lock lock(mtx);
        mCV.wait(lock, [this]{
          return !mSpmcQueue.empty() || mDone;
        });
        if (mDone) {
            break;
        }
        int fd;
        if (!mSpmcQueue.pop(fd)) {
            continue;
        }
        Socket connection(fd);
        string msg = connection.ReadAllBytes(4096);
        auto [request, status] = build_request(msg, doc_root);

    }

}