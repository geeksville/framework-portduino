//
// Created by kevinh on 9/1/20.
//
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>

extern "C" uint32_t micros(void) {
  struct timeval te;
  gettimeofday(&te, NULL);                                  // get current time
  uint32_t usecs = te.tv_sec * 1000000LL + te.tv_usec; // calculate
  // printf("usecs %lu\n", usecs);
  return usecs;
}

extern "C" uint32_t millis(void) {
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  uint32_t milliseconds =
      te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
  // printf("milliseconds: %llu\n", milliseconds);
  return milliseconds;
}