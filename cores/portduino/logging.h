#pragma once

#include <cstdarg>

// FIXME - move somewhere else and add gcc arg type hints

enum LogLevel { LogVerbose, LogDebug, LogInfo, LogWarn, LogError };

enum LogSystem {
  SysCurrent = 0, // The last set current subsystem
  SysUnknown,
  SysCore,
  SysI2C,

  // Ids greater than 1000 are used for application specific purposes
  SysApp0 = 1000
};

void log(LogSystem sys, LogLevel level, const char *fmt, ...);
void log(LogSystem sys, LogLevel level, const char *fmt, va_list args);

void log_e(const char *fmt, ...);
void log_w(const char *fmt, ...);
void log_i(const char *fmt, ...);
void log_d(const char *fmt, ...);
void log_v(const char *fmt, ...);