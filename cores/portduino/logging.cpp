#include "logging.h"
#include "Utility.h"



void log(LogSystem sys, LogLevel level, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(sys, level, fmt, args);
  va_end(args);
}

void log(LogSystem sys, LogLevel level, const char *fmt, va_list args) {
  notImplemented("log");
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