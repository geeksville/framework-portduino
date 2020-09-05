//
// Created by kevinh on 9/1/20.
//

#ifndef PORTDUINO_SIMHARDWAREI2C_H
#define PORTDUINO_SIMHARDWAREI2C_H

#include "HardwareI2C.h"
#include "Utility.h"

namespace arduino {

    class SimHardwareI2C : public HardwareI2C {
    public:
        virtual void begin() NOT_IMPLEMENTED("begin")

        virtual void begin(uint8_t address) NOT_IMPLEMENTED("begin")

        virtual void end() NOT_IMPLEMENTED("end")

        virtual void setClock(uint32_t freq) NOT_IMPLEMENTED("setClock")

        virtual void beginTransmission(uint8_t address) NOT_IMPLEMENTED("beginTransmission")

        virtual uint8_t endTransmission(bool stopBit) {
            notImplemented("endTransmission");
            return 0;
        }

        virtual uint8_t endTransmission(void) {
            notImplemented("endTransmission");
            return 0;
        }

        virtual uint8_t requestFrom(uint8_t address, size_t len, bool stopBit) {
            notImplemented("requestFrom");
            return 0;
        }

        virtual uint8_t requestFrom(uint8_t address, size_t len) {
            notImplemented("requestFrom");
            return 0;
        }

        virtual void onReceive(void(*)(int)) NOT_IMPLEMENTED("onReceive")

        virtual void onRequest(void(*)(void)) NOT_IMPLEMENTED("onRequest")

        // Methods from Print

        virtual size_t write(uint8_t) {
            notImplemented("write");
            return 0;
        }

        // Methods from Stream

        virtual int available() {
            notImplemented("available");
            return 0;
        }

        virtual int read() {
            notImplemented("read");
            return 0;
        }

        virtual int peek() {
            notImplemented("peek");
            return 0;
        }
    };

    extern SimHardwareI2C Wire;
}

#endif //PORTDUINO_SIMHARDWAREI2C_H
