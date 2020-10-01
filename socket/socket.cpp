//
// Created by alexandr on 01.10.2020.
//

#include "socket.h"

Socket::Socket(int sock_fd) : mSockFD(sock_fd){}

Socket::Socket(Socket && sock) : mSockFD(sock.mSockFD.Extract()){}

Socket& Socket::operator=(Socket &&sock) {
    Close();
    mSockFD = sock.mSockFD.Extract();
    return *this;
}

void Socket::Close() {
    mSockFD.Close();
}

size_t Socket::Write(const void *data, size_t length) const {
    while(true) {
        ssize_t  bytes_wrote = write(mSockFD, data, length);
        if (bytes_wrote < 0) {
            if (errno == EINTR) {
                continue;
            }
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return 0;
            }

            throw "Cannnot write to docket";
        }
        return static_cast<size_t>(bytes_wrote);
    }
}

void Socket::WriteExactData(const void *data, size_t length) const {
    size_t bytes_wrote = 0;
    while(bytes_wrote != length) {
        const void * buff_begin = static_cast<const char *>(data) + bytes_wrote;

        size_t bytes_wrote = Write(buff_begin, length - bytes_wrote);
        if (bytes_wrote == 0) {
            throw "Unable to write " + std::to_string(length) + " bytes":
        }
        bytes_wrote += bytes_wrote;
    }
}

size_t Socket::Read(void *data, size_t length) {
    while(true) {
        ssize_t bytes_read = read(mSockFD, data, length);

        if (bytes_read < 0) {
            if (errno == EINTR) {
                continue;
            }
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                return 0;
            }
            throw "Cannot read from socket";
        }
        return static_cast<size_t>(bytes_read);
    }
}

std::string Socket::ReadAllBytes(long limit) {
    std::ostringstream ostringstream;
    while (ostringstream.tellp() < limit) {
        std::string block(1024, '\0');
        size_t bytes_read = Read(block.data(), block.size());

        ostringstream.write(block.c_str(), static_cast<long>(bytes_read));

        if (bytes_read < block.size()) {
            break;
        }
    }
    return ostringstream.str();
}

size_t Socket::SendFile(std::string_view filePath) {
    FileScopeGuard fileFd = open(filePath.data(), O_RDONLY);
    if (fileFd < 0 ) {
        throw "Cannot send file to socket";
    }
    while (true) {
        ssize_t bytes_wrote = sendfile(mSockFD, fileFd, nullptr, std::filesystem::file_size(filePath));

        if (bytes_wrote < 0) {
            if (errno == EINTR) {
                continue;
            }
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return 0;
            }
            throw "Cannot send file to socket";
        }
        return static_cast<size_t>(bytes_wrote);
    }
}