//
// Created by kevinh on 9/1/20.
//

#include "Common.h"
#include "Utility.h"

#include <time.h>

void pinMode(pin_size_t pinNumber, PinMode pinMode) NOT_IMPLEMENTED("pinMode")

void digitalWrite(pin_size_t pinNumber, PinStatus status) NOT_IMPLEMENTED("digitalWrite")

PinStatus digitalRead(pin_size_t pinNumber) {
    notImplemented("digitalRead");
    return LOW;
}

int analogRead(pin_size_t pinNumber) {
    notImplemented("analogRead");
    return 0;
}


void analogWrite(pin_size_t pinNumber, int value) NOT_IMPLEMENTED("analogWrite")

void delay(unsigned long milliSec) {
    timespec ts{.tv_sec = (time_t) (milliSec / 1000), .tv_nsec = (long) (milliSec % 1000) * 1000L * 1000L};
    nanosleep(&ts, NULL);
}

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode) NOT_IMPLEMENTED(
        "attachInterrupt")

void detachInterrupt(pin_size_t interruptNumber) NOT_IMPLEMENTED("detachInterrupt")