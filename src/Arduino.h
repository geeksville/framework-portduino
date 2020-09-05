#pragma once

#include "ArduinoAPI.h"
#include "HardwareSPI.h"
#include "linux/LinuxSerial.h"
#include "simulated/SimHardwareI2C.h"

extern HardwareSPI SPI;

using namespace arduino;

typedef HardwareI2C TwoWire; // Some Arduino ports use this terminology

/** Map a pin number to an interrupt # 
 * We always map 1:1
*/
inline pin_size_t digitalPinToInterrupt(pin_size_t pinNumber) { return pinNumber; }