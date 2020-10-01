
#ifndef FAST_WEB_SERVER_SOCKET_SCOPE_GUARD_H_
#define FAST_WEB_SERVER_SOCKET_SCOPE_GUARD_H_

class FileScopeGuard {
  int mFD = -1;
 public:
    FileScopeGuard() = default;
    FileScopeGuard(int fd);
    FileScopeGuard(FileScopeGuard&& file);
    ~FileScopeGuard();

    FileScopeGuard(const FileScopeGuard & file) = delete;
    FileScopeGuard & operator = (int fd);

    operator int() const;
    void Close();
    int Extract();

    bool IsOpened() const;

};

#endif //FAST_WEB_SERVER_SOCKET_SCOPE_GUARD_H_
