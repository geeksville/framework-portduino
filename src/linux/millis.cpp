//
// Created by kevinh on 9/1/20.
//
#include <sys/time.h>
#include <stdlib.h>

extern "C" unsigned long millis(void) {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}