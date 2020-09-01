#include <stdio.h>
#include "Arduino.h"

int main(int argc, const char **argv) {
  printf("hello world\n");
  setup();
  while(true)
      loop();
  return 0;
}