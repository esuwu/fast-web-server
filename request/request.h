
#ifndef FAST_WEB_SERVER_REQUEST_REQUEST_H_
#define FAST_WEB_SERVER_REQUEST_REQUEST_H_

#include <string>
#include "../http/http.h"

class Request {
 public:
  std::string_view version;
  method::Type method;
  std::string path;

};

std::tuple<Request, const std::string> build_request(const std::string_view &request_cv, const std::string & document_sv_root);

class RequestConstruct {
 public:
  RequestConstruct() = default;
    std::tuple<Request, status::Type> operator()(const std::string_view & request_cv, const std::string_view & document_sv_root);
 private:
  std::string_view mRequestSV;
  Request mRequest{};
  status::Type mStatus = status::Status_200_OK;
  void GetHTTPMethod();
  bool CheckMethod();
  void GetPath();
  bool CheckPath(const std::string_view & document_sv_root);
  void GetVersion();
  bool CheckVersion();
};



#endif //FAST_WEB_SERVER_REQUEST_REQUEST_H_
