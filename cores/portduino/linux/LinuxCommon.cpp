//
// Created by kevinh on 9/1/20.
//

#include "Common.h"
#include "Utility.h"

#include <time.h>

void delay(unsigned long milliSec) {
  timespec ts{.tv_sec = (time_t)(milliSec / 1000),
              .tv_nsec = (long)(milliSec % 1000) * 1000L * 1000L};
  nanosleep(&ts, NULL);
}

void delayMicroseconds(unsigned int usec) {
  timespec ts{.tv_sec = (time_t)(usec / 1000000L),
              .tv_nsec = (long)(usec % 1000000L) * 1000L};
  nanosleep(&ts, NULL);
}

void yield(void) { notImplemented("yield"); }

long random(long max) { return random(0, max); }

long random(long min, long max) {
  notImplemented("random");
  return 0L;
}

void randomSeed(unsigned long) { notImplemented("randseed"); }

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
    NOT_IMPLEMENTED("tone");

void noTone(uint8_t _pin) NOT_IMPLEMENTED("noTone");