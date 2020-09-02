//
// Created by kevinh on 9/1/20.
//

#include "LinuxSerial.h"

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
        return 0;
    }

    int LinuxSerial::read(void) {
        return 0;
    }

    void LinuxSerial::flush(void) {

    }

    size_t LinuxSerial::write(uint8_t) {
        return 1;
    }

    LinuxSerial::operator bool() {
        return false;
    }
}