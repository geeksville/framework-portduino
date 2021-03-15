//
// Created by kevinh on 9/1/20.
//

#ifndef PORTDUINO_UTILITY_H
#define PORTDUINO_UTILITY_H

void notImplemented(const char *msg);

// Used as a suffix added after a method/function declaration
#define NOT_IMPLEMENTED(msg)                                                   \
  { notImplemented(msg); }

/**
 * Normally arduino apps don't use exceptions.  If exceptions are allowed an exception will be thrown, otherwise an error message will be printed
 * and the function will return.
 */
void portduinoError(const char *msg, ...);

/** Trigger a debugger breakpoint if in the debugger 
 */
void portduinoDebug();

#endif // PORTDUINO_UTILITY_H
