
#ifndef FAST_WEB_SERVER_SERVER_SERVER_H_
#define FAST_WEB_SERVER_SERVER_SERVER_H_

#include <thread>
#include "../socket/scope_guard.h"
#include "../socket/socket.h"
#include "../http/http.h"
#include <vector>
#include <condition_variable>
#include <boost/lockfree/queue.hpp>
#include <sys/epoll.h>

using namespace std;

class Server {
  using threadPool = vector<thread>;
 public:
  Server(const Server & server) = delete;
  Server(Server && server) = delete;
  Server & operator =(const Server& server) = delete;
  Server& operator=(Server && server) = delete;

  static Server& Start(const string_view& address, uint16_t port, size_t max_connection, size_t max_thread,
                       const string& doc_root);
  static Server& GetInstance();

  void Open(const string_view& address, uint16_t);
  void Listen(int maxConnect);

  void Close();
  void JoinWorkers();

  bool IsOpened() const;
  void Run();

 private:
  FileScopeGuard mSockFD;
  FileScopeGuard mEpollFD;

  threadPool mWorkers;
  condition_variable mCV;
  bool mDone = false;
  boost::lockfree::queue<int> mSpmcQueue;

  Server(const string_view& address, uint16_t port, size_t max_connection, size_t max_thread,
                       const string& doc_root);
  ~Server();
  static void HandleSignal(int);
  void CreateEpoll();
  void AddEpoll(int FD, uint32_t events) const;
  void AcceptClients();
  void HandleClients(int fd, epoll_event event);
  void Work(const string & doc_root);

};

#endif //FAST_WEB_SERVER_SERVER_SERVER_H_
