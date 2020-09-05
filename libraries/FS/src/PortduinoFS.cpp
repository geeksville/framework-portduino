#include "PortduinoFS.h"

static VFSImpl vfs;
static FSImplPtr vfsImpl(&vfs);
FS PortduinoFS = FS(vfsImpl);