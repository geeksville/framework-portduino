#include "Arduino.h"
#include "PortduinoFS.h"
#include "PortduinoGPIO.h"
#include <stdio.h>

/** # msecs to sleep each loop invocation.  FIXME - make this controlable via
 * config file or command line flags.
 */
static long loopDelay = 100;

/** apps run under portduino can optionally define a portduinoSetup() to 
 * use portduino specific init code (such as gpioBind) to setup portduino on their host machine,
 * before running 'arduino' code.
 */
void __attribute__((weak)) portduinoSetup() {
  printf("No portduinoSetup() found, using default settings...\n");
}

int main(int argc, const char **argv) {
  printf("Portduino is starting\n");

  String fsroot("/tmp/portduinofs");
  mkdir(fsroot.c_str(), 0777);
  portduinoVFS.mountpoint(fsroot.c_str());

  gpioInit();
  portduinoSetup();
  setup();
  while (true) {
    gpioIdle(); // FIXME, do this someplace better
    loop();

    // Even if the Arduino code doesn't want to sleep, ensure we don't  burn too
    // much CPU
    delay(loopDelay);
  }
  return 0;
}