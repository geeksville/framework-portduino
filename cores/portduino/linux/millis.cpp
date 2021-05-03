//
// Created by kevinh on 9/1/20.
//
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>

extern "C" unsigned long micros(void) {
  struct timeval te;
  gettimeofday(&te, NULL);                                  // get current time
  unsigned long usecs = te.tv_sec * 1000000LL + te.tv_usec; // calculate
  // printf("usecs %lu\n", usecs);
  return usecs;
}

static unsigned long startMsec;

/**
 * Return msecs since this 'arduino' instance started running
 */
extern "C" unsigned long millis(void) {
  struct timeval te;
  gettimeofday(&te, NULL); // get current time

  unsigned long milliseconds =
      te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds

  if(startMsec == 0) // First run
    startMsec = milliseconds;

  return milliseconds - startMsec;
}