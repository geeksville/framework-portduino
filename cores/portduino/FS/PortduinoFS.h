#pragma once

#include "vfs_api.h"

extern fs::FS PortduinoFS;

extern std::shared_ptr<VFSImpl> portduinoVFS; // Do not use directly, instead use PortduinoFS
