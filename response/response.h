//
// Created by alexandr on 01.10.2020.
//

#ifndef FAST_WEB_SERVER_RESPONSE_RESPONSE_H_
#define FAST_WEB_SERVER_RESPONSE_RESPONSE_H_
#include "../socket/socket.h"
#include "../request/request.h"
#include <string_view>


void build_and_send_resp(Socket & conn, const Request & request, status::Type& status);

class ResponseConstruct {
 public:
  ResponseConstruct() = default;
  void operator()(Socket & conn, const Request& request, status::Type& status);
 private:
  std::ostringstream Oss;
  void CheckFileAvailable(const std::string_view& filePath, status::Type & status);
  void WriteHeader(const Request& request, status::Type& status);
};

#endif //FAST_WEB_SERVER_RESPONSE_RESPONSE_H_
