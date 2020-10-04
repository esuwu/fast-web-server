//
// Created by alexandr on 01.10.2020.
//

#include "scope_guard.h"
#include <utility>
#include <unistd.h>
#include <iostream>
#include <exception>

FileScopeGuard::FileScopeGuard(int fd) : mFD(fd){}

FileScopeGuard::FileScopeGuard(FileScopeGuard && file) : mFD(std::exchange(file.mFD, -1)){}

FileScopeGuard::~FileScopeGuard() {
    try {
        Close();
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Exception in destructor FileScopeGuard" << std::endl;
    }
}

FileScopeGuard& FileScopeGuard::operator=(int fd)  {
    Close();
    mFD = fd;
    return *this;
}

FileScopeGuard::operator int() const {
    return mFD;
}

void FileScopeGuard::Close() {
    if (mFD == -1) {
        return;
    }

    while(close(mFD) != 0) {
        if (errno == EINTR) {
            continue;
        }
        throw "Cannot close file descriptor in func Close";
    }

    mFD = -1;
}

int FileScopeGuard::Extract() {
    return std::exchange(mFD, -1);
}

bool FileScopeGuard::IsOpened() const {
    return mFD != -1;
}