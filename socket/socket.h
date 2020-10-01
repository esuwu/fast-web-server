//
// Created by alexandr on 01.10.2020.
//

#ifndef FAST_WEB_SERVER_SOCKET_SOCKET_H_
#define FAST_WEB_SERVER_SOCKET_SOCKET_H_

#include <sys/fcntl.h>
#include <sys/sendfile.h>
#include "scope_guard.h"
#include <unistd.h>
#include <filesystem>

class Socket {
 public:
  explicit Socket(int sock_fd);
  ~Socket() = default;
  Socket(Socket && sock);
  Socket & operator=(Socket && sock);

  Socket(const Socket & sock) = delete;
  Socket & operator=(const Socket & sock) = delete;

  void Close();

  size_t Write(const void * data, size_t length) const;
  void WriteExactData(const void * data, size_t length) const;
  size_t Read(void * data, size_t length);
  std::string ReadAllBytes(long limit);

  size_t SendFile(std::string_view filePath);
 private:
  FileScopeGuard mSockFD;
};

#endif //FAST_WEB_SERVER_SOCKET_SOCKET_H_
