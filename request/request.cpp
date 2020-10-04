//
// Created by alexandr on 01.10.2020.
//

#include "request.h"
#include <tuple>



std::tuple<Request, status::Type> RequestConstruct::operator()(const std::string_view & request_sv, const std::string_view & doc_root_sv) {
    mRequestSV = request_sv;

    GetHTTPMethod();
    GetPath();
    GetVersion();

    CheckMethod() && CheckPath(doc_root_sv) && CheckVersion();
    return std::make_tuple(mRequest, mStatus);
}

std::tuple<Request, status::Type> build_request(const std::string_view &request_cv, const std::string & document_sv_root){
    RequestConstruct rb;
    return rb(request_cv, document_sv_root);
}





void RequestConstruct::GetHTTPMethod() {
    size_t pos = mRequestSV.find(" /");

    mRequest.method = mRequestSV.substr(0, pos);
    mRequestSV.remove_prefix(pos + 1);
}


void RequestConstruct::GetPath() {
    size_t pos = mRequestSV.find(" HTTP/");

    mRequest.path = mRequestSV.substr(0, pos);
    mRequestSV.remove_prefix(pos + 1);
}


void RequestConstruct::GetVersion() {
    size_t pos = mRequestSV.find(End_Of_Line);

    mRequest.version = mRequestSV.substr(0, pos);
    mRequestSV.remove_prefix(pos);
}


bool RequestConstruct::CheckMethod() {
    if (mRequest.method != method::Method_GET &&
        mRequest.method != method::Method_HEAD)
    {
        mStatus = status::Status_405_Not_Allowed;
        return false;
    }

    return true;
}


bool RequestConstruct::CheckPath(const std::string_view &document_sv_root) {
    size_t query_string_pos = mRequest.path.find('?');
    if (query_string_pos != std::string::npos) {
        mRequest.path.resize(query_string_pos);
    }

    if (mRequest.path.find("../") != std::string::npos) {
        mStatus = status::Status_403_Forbidden;
        return false;
    }

    mRequest.path = document_sv_root.data() + mRequest.path;
    if (mRequest.path.ends_with('/')) {
        mRequest.path += "index.html";
    }

    for (size_t url_encode_pos = mRequest.path.find('%'); url_encode_pos != std::string::npos; url_encode_pos = mRequest.path.find('%')) {
        std::string_view url_encode = static_cast<std::string_view>(mRequest.path).substr(url_encode_pos + 1, 2);

        char url_decode = static_cast<char>(std::stoul(url_encode.data(), nullptr, 16));
        if (url_decode == 0) {
            continue;
        }

        mRequest.path.replace(url_encode_pos, 3, 1, url_decode);
    }

    return true;
}


bool RequestConstruct::CheckVersion() {
    if (!mRequest.version.starts_with("HTTP/")) {
        mStatus = status::Status_400_Bad_Request;
        return false;
    }

    if (!mRequestSV.starts_with(End_Of_Line)) {
        mStatus = status::Status_400_Bad_Request;
        return false;
    }
    return true;
}

