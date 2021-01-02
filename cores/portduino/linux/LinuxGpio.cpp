//
// Created by kevinh on 9/1/20.
//

#include "Common.h"
#include "Utility.h"
#include "logging.h"
#include "Arduino.h"
#include "PortduinoGPIO.h"

#include <assert.h>
#include <stdlib.h>

#include "linux/GPIOChip.h"

class LinuxGPIOPin : public GPIOPin
{
  GPIOLines *line;

public:
  LinuxGPIOPin(pin_size_t n, String _name, GPIOLines *l) : GPIOPin(n, _name), line(l) {}

protected:
  /// Read the low level hardware for this pin
  virtual PinStatus readPinHardware();
  virtual void writePin(PinStatus s);
  virtual void setPinMode(PinMode m);
};
