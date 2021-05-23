//
// Created by kevinh on 9/1/20.
//

#ifdef PORTDUINO_LINUX_HARDWARE

#include "Arduino.h"
#include "Common.h"
#include "PortduinoGPIO.h"
#include "Utility.h"
#include "logging.h"

#include <assert.h>
#include <stdlib.h>
#include <gpiod.h>



/**
 * Adapts the modern linux GPIO API for use by Portduino
 */
class LinuxGPIOPin : public GPIOPin {
  /// Our GPIO line
  struct gpiod_line *line;

public:

  /**
    * Create a pin given a linux chip label and pin name
    */
  LinuxGPIOPin(pin_size_t n, const char *chipLabel, const char *linuxPinName, const char *portduinoPinName = NULL);

  /**
   * Constructor
   * @param l is the low level linux GPIO pin object
   */
  // LinuxGPIOPin(pin_size_t n, String _name, struct gpiod_line *l)
  //    : GPIOPin(n, _name), line(l) {}

  ~LinuxGPIOPin();

protected:
  /// Read the low level hardware for this pin
  virtual PinStatus readPinHardware();
  virtual void writePin(PinStatus s);
  virtual void setPinMode(PinMode m);
};

#endif