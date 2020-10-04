//
// Created by alexandr on 01.10.2020.
//

#include "response.h"

void build_and_send_resp(Socket & conn, const Request & request, status::Type& status) {
    ResponseConstruct response_constructer;
    return response_constructer(conn, request, status);
}

void ResponseConstruct::operator()(Socket &conn, const Request &request, status::Type &status) {
    namespace fd = std::filesystem;

    CheckFileAvailable(request.path, status);

    WriteHeader(request, status);

    conn.WriteExactData(Oss.str().c_str(), static_cast<size_t>(Oss.tellp()));

    if (status == status::Status_200_OK && request.method == method::Method_GET) {
        conn.SendFile(request.path);
    }
}

void ResponseConstruct::WriteHeader(const Request &request, status::Type &status) {
    Oss << request.version << ' ' << status << End_Of_Line
    << "Server: fast-http-server" << End_Of_Line
    << "Date: " << __DATE__ << ' ' << __TIME__ << End_Of_Line
    << "Connection: Close" << End_Of_Line;

    if (status == status::Status_200_OK) {
        Oss << "Content-Length: " << std::filesystem::file_size(request.path) << End_Of_Line
        << "Content-Type: " << mime_type::GetContentType(request.path) << End_Of_Line;
    }
    Oss << End_Of_Line;
}

void ResponseConstruct::CheckFileAvailable(const std::string_view &filePath, status::Type &status) {
    if (status == status::Status_200_OK && !std::filesystem::exists(filePath)) {
        if (filePath.ends_with("index.html")) {
            status = status::Status_403_Forbidden;
        } else {
            status = status::Status_404_Not_Found;
        }
    }
}