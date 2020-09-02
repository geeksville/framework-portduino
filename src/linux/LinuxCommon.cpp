//
// Created by kevinh on 9/1/20.
//

#include "Common.h"

#include <time.h>

void delay(unsigned long milliSec) {
    timespec ts{.tv_sec = (time_t) (milliSec / 1000), .tv_nsec = (long) (milliSec % 1000) * 1000L * 1000L};
    nanosleep(&ts, NULL);
}
