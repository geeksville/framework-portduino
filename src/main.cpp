#include <stdio.h>
#include "Arduino.h"

/** # msecs to sleep each loop invocation.  FIXME - make this controlable via config file or command
 * line flags.
 */
static long loopDelay = 100;

int main(int argc, const char **argv) {
  printf("hello world\n");
  setup();
  while(true) {
      loop();

      // Even if the Arduino code doesn't want to sleep, ensure we don't  burn too much CPU
      delay(loopDelay);
  }
  return 0;
}