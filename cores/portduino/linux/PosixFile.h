#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include "Utility.h"

/** A posix file descriptor based file
 */

class PosixFile
{
    int fd;

public:
    PosixFile(const char *path, int mode = 0)
    {
        fd = open(path, mode);
        if (fd == -1)
            portduinoError("Failed to open posix file %s, errno=%d", path, errno); // FIXME, find a more structured/standard way to throw C++ OS exceptions
    }

    PosixFile(int _fd) : fd(_fd) {}

    ~PosixFile()
    {
        if (fd >= 0)
            close(fd);
        fd = -1;
    }

    int ioctl(unsigned long op, void *arg)
    {
        if(fd < 0)
            return fd;

        auto ret = ::ioctl(fd, op, arg);
        if (ret == -1)
            throw -errno;
        return ret;
    }
};