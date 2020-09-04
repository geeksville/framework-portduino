#pragma once

#include "ArduinoAPI.h"
#include "HardwareSPI.h"
#include "linux/LinuxSerial.h"
#include "simulated/SimHardwareI2C.h"

extern HardwareSPI SPI;

using namespace arduino;

typedef HardwareI2C TwoWire; // Some Arduino ports use this terminology
