#include "logging.h"
#include "Utility.h"

#include <Arduino.h>

void log(LogSystem sys, LogLevel level, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(sys, level, fmt, args);
  va_end(args);
}

void log(LogSystem sys, LogLevel level, const char *fmt, va_list args) {
  char buf[256]; // FIXME - this takes up lots of stack space
  vsnprintf(buf, sizeof(buf), fmt, args);
  Serial.write(buf);
  Serial.write('\n'); // FIXME make logging smarter
}

void log_e(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(SysCurrent, LogError, fmt, args);
  va_end(args);
}

void log_w(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(SysCurrent, LogWarn, fmt, args);
  va_end(args);
}

void log_i(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(SysCurrent, LogInfo, fmt, args);
  va_end(args);
}

void log_d(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(SysCurrent, LogDebug, fmt, args);
  va_end(args);
}

void log_v(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(SysCurrent, LogVerbose, fmt, args);
  va_end(args);
}