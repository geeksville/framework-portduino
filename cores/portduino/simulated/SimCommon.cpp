//
// Created by kevinh on 9/1/20.
//

#include "Common.h"
#include "Utility.h"
#include "logging.h"

void pinMode(pin_size_t pinNumber, PinMode pinMode) {
  log(SysGPIO, LogDebug, "SIM: pinMode(%d, %d)", pinNumber, pinMode);
}

void digitalWrite(pin_size_t pinNumber, PinStatus status) {
  log(SysGPIO, LogDebug, "SIM: digitalWrite(%d, %d)", pinNumber, status);
}

PinStatus digitalRead(pin_size_t pinNumber) {
  PinStatus v = LOW;
  log(SysGPIO, LogDebug, "SIM: digitalRead(%d) -> %d", pinNumber, v);
  return v;
}

int analogRead(pin_size_t pinNumber) {
  int v = 42;
  log(SysGPIO, LogDebug, "SIM: analogRead(%d) -> %d", pinNumber, v);
  return v;
}

void analogWrite(pin_size_t pinNumber, int value)
    NOT_IMPLEMENTED("analogWrite");

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback,
                     PinStatus mode) NOT_IMPLEMENTED("attachInterrupt");

void detachInterrupt(pin_size_t interruptNumber)
    NOT_IMPLEMENTED("detachInterrupt");