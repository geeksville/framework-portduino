#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

/** A posix file descriptor based file
 */

class PosixFile {
    int fd;

public:
    PosixFile(const char *path, int mode = 0) {
        fd = open(path, mode);
        if (fd == -1) 
            throw -errno; // FIXME, find a more structured/standard way to throw C++ OS exceptions
    }

    PosixFile(int _fd) : fd(_fd) {}

    ~PosixFile() {
        if(fd >= 0)
            close(fd);
    }

    int ioctl(unsigned long op, void *arg) {
        auto ret = ::ioctl(fd, op, arg);
        if(ret == -1)
            throw -errno;
        return ret;
    }
};