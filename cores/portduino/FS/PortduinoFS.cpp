#include "PortduinoFS.h"

// Do not use directly, instead use PortduinoFS
std::shared_ptr<VFSImpl> portduinoVFS = std::make_shared<VFSImpl>();
// std::shared_ptr<VFSImpl> portduinoVFS(new VFSImpl());

FS PortduinoFS = FS(portduinoVFS);