//
// Created by kevinh on 9/1/20.
//

#include "Common.h"
#include "Utility.h"
#include "logging.h"
#include "Arduino.h"
#include "PortduinoGPIO.h"

#include <assert.h>
#include <stdlib.h>

// #include "linux/gpio/classic/GPIOChip.h"

#define NUM_GPIOS 64

static GPIOPinIf *pins[NUM_GPIOS];


/** By default we assign simulated GPIOs to all pins, later applications can customize this in portduinoSetup */
void gpioInit() {
  for(size_t i = 0; i < NUM_GPIOS; i++)
    pins[i] = new SimGPIOPin(i, "Unbound");
}

void gpioIdle() {
  // log(SysGPIO, LogDebug, "doing idle refresh");
  for(size_t i = 0; i < NUM_GPIOS; i++)
    pins[i]->refreshIfNeeded();
}

void gpioBind(GPIOPinIf *p) {
    assert(p->getPinNum() < NUM_GPIOS);
    pins[p->getPinNum()] = p;
}

/**
 * Return the specified GPIO pin or the UnboundPin pin instance */
GPIOPinIf *getGPIO(pin_size_t n)
{
  assert(n < NUM_GPIOS);
  auto p = pins[n];

  assert(p);
  return p;
}

void pinMode(pin_size_t pinNumber, PinMode pinMode)
{
  // log(SysGPIO, LogDebug, "pinMode(%d, %d)", pinNumber, pinMode);
  auto p = getGPIO(pinNumber);
  p->setPinMode(pinMode);
}

void digitalWrite(pin_size_t pinNumber, PinStatus status)
{
  // log(SysGPIO, LogDebug, "digitalWrite(%d, %d)", pinNumber, status);
  auto p = getGPIO(pinNumber);
  p->writePin(status);
}

PinStatus digitalRead(pin_size_t pinNumber)
{
  auto p = getGPIO(pinNumber);
  auto r = p->readPin();

  // log(SysGPIO, LogDebug, "digitalRead(%d) -> %d", pinNumber, r);
  return r;
}

unsigned long pulseIn(pin_size_t pinNumber, PinStatus status, unsigned long timeout)
{
  auto p = getGPIO(pinNumber);
  auto r = p->pulseIn(status, timeout);

  // log(SysGPIO, LogDebug, "pulseIn(%d) -> %d", pinNumber, r);
  return r;
}

int analogRead(pin_size_t pinNumber)
{
  auto p = getGPIO(pinNumber);
  auto r = p->analogRead();

  log(SysGPIO, LogDebug, "analogRead(%d) -> %d", pinNumber, r);
  return r;
}

void analogWrite(pin_size_t pinNumber, int value)
{
  auto p = getGPIO(pinNumber);

  log(SysGPIO, LogDebug, "analogWrite(%d) -> %d", pinNumber, value);
  p->analogWrite(value);
}

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback,
                     PinStatus mode)
{
  //log(SysInterrupt, LogDebug, "attachInterrupt %d", interruptNumber);
  auto p = getGPIO(interruptNumber);
  p->attachInterrupt(callback, mode);
}

void detachInterrupt(pin_size_t interruptNumber)
{
  //log(SysInterrupt, LogDebug, "detachInterrupt %d", interruptNumber);
  auto p = getGPIO(interruptNumber);
  p->detachInterrupt();
}