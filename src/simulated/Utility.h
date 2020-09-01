//
// Created by kevinh on 9/1/20.
//

#ifndef PORTDUINO_UTILITY_H
#define PORTDUINO_UTILITY_H

void notImplemented(const char *msg);

// Used as a suffix added after a method/function declaration
#define NOT_IMPLEMENTED(msg) { notImplemented(msg); };

#endif //PORTDUINO_UTILITY_H
