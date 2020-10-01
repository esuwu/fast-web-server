//
// Created by alexandr on 01.10.2020.
//

#include "http.h"
#include <string>
mime_type::Type mime_type::GetContentType(const std::string_view & file_path) {
    if (file_path.ends_with("html") || file_path.ends_with("htm")) {
        return mime_type::Mime_Type_HTML;
    }
    else if (file_path.ends_with("css")) {
        return mime_type::Mime_Type_CSS;
    }
    else if (file_path.ends_with("gif")) {
        return mime_type::Mime_Type_GIF;
    }
    else if (file_path.ends_with("png")) {
        return mime_type::Mime_Type_PNG;
    }
    else if (file_path.ends_with("jpg") || file_path.ends_with("jpe") || file_path.ends_with("jpeg")) {
        return mime_type::Mime_Type_JPG;
    }
    else if (file_path.ends_with("tiff") || file_path.ends_with("tif")) {
        return mime_type::Mime_Type_TIFF;
    }
    else if (file_path.ends_with("bmp")) {
        return mime_type::Mime_Type_BMP;
    }
    else if (file_path.ends_with("js")) {
        return mime_type::Mime_Type_JS;
    }
    else if (file_path.ends_with("swf")) {
        return mime_type::Mime_Type_SWF;
    }
    return mime_type::Mime_Type_PLAIN;
}

