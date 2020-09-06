#include "Arduino.h"
#include "PortduinoFS.h"
#include <stdio.h>

/** # msecs to sleep each loop invocation.  FIXME - make this controlable via
 * config file or command line flags.
 */
static long loopDelay = 100;

int main(int argc, const char **argv) {
  printf("Portduino is starting\n");

  String fsroot("/tmp/portduinofs");
  mkdir(fsroot.c_str(), 0777);
  portduinoVFS.mountpoint(fsroot.c_str());

  setup();
  while (true) {
    loop();

    // Even if the Arduino code doesn't want to sleep, ensure we don't  burn too
    // much CPU
    delay(loopDelay);
  }
  return 0;
}