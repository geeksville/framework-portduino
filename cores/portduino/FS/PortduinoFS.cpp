#include "PortduinoFS.h"

VFSImpl portduinoVFS; // Do not use directly, instead use PortduinoFS
static FSImplPtr vfsImpl(&portduinoVFS);
FS PortduinoFS = FS(vfsImpl);