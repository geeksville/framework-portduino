//
// Created by kevinh on 9/1/20.
//

#include "LinuxSerial.h"

#include <stdio.h>

namespace arduino {
    LinuxSerial Serial;

    void LinuxSerial::begin(unsigned long baudrate, uint16_t config) {
        // Ignore baudrate and config on linux (for now)
        // FIXME open file descriptor
    }

    void LinuxSerial::end() {
        // FIXME - close file descriptor
    }

    int LinuxSerial::available(void) {
        return 0;
    }

    int LinuxSerial::peek(void) {
        return -1;
    }

    int LinuxSerial::read(void) {
        return -1;
    }

    void LinuxSerial::flush(void) {
    }

    size_t LinuxSerial::write(uint8_t c) {
        putchar(c);
        return 1;
    }

    LinuxSerial::operator bool() {
        // Returns true if the port is ready for use
        return true;
    }
}