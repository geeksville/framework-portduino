//
// Created by kevinh on 9/1/20.
//

#include <stdio.h>
#include "Utility.h"

void notImplemented(const char *msg) {
    printf("%s is not implemented\n", msg);
}

void portduinoError(const char *msg, ...) {
    printf("Portduino critical error: %s\n", msg);
}