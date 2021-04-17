//
// Created by kevinh on 9/1/20.
//

#include "Arduino.h"
#include "Common.h"
#include "PortduinoGPIO.h"
#include "Utility.h"
#include "logging.h"

#include <assert.h>
#include <stdlib.h>

#include "linux/GPIOChip.h"

namespace classic_linux_gpio {

/**
 * Adapts the classic_linux_gpio API for use by Portduino
 */
class LinuxGPIOPin : public GPIOPin {
  GPIOLines *line;

public:
  /**
   * Constructor
   * @param l is the low level linux GPIO pin object
   */
  LinuxGPIOPin(pin_size_t n, String _name, GPIOLines *l)
      : GPIOPin(n, _name), line(l) {}

protected:
  /// Read the low level hardware for this pin
  virtual PinStatus readPinHardware();
  virtual void writePin(PinStatus s);
  virtual void setPinMode(PinMode m);
};

} // namespace classic_linux_gpio
