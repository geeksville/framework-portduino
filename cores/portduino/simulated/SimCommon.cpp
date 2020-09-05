//
// Created by kevinh on 9/1/20.
//

#include "Common.h"
#include "Utility.h"

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

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode) NOT_IMPLEMENTED(
        "attachInterrupt")

void detachInterrupt(pin_size_t interruptNumber) NOT_IMPLEMENTED("detachInterrupt")