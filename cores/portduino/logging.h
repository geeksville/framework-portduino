#pragma once

#include <cstdarg>

namespace arduino {

// FIXME - move somewhere else and add gcc arg type hints

enum LogLevel { LogVerbose, LogDebug, LogInfo, LogWarn, LogError };

enum LogSystem {
  SysCurrent = 0, // The last set current subsystem
  SysUnknown,
  SysCore,
  SysGPIO,
  SysI2C,
  SysSPI,
  SysInterrupt,
  SysWifi,

  // Ids greater than 1000 are used for application specific purposes
  SysApp0 = 1000
};

void log(LogSystem sys, LogLevel level, const char *fmt, ...)
    __attribute__((format(printf, 3, 4)));
void logv(LogSystem sys, LogLevel level, const char *fmt, va_list args);

void log_e(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void log_w(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void log_i(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void log_d(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void log_v(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

}