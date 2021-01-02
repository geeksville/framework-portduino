#pragma once

#include "Common.h"
#include "Utility.h"
#include "logging.h"
#include "Arduino.h"

#include <assert.h>
#include <stdlib.h>

/**
 * The standard interface to a single GPIO line.  A given implementation subclass might be SimGPIOPin or
 * LinuxGPIOPin etc...
 */
class GPIOPinIf
{
public:
    virtual pin_size_t getPinNum() const = 0;

    /** Called to read from a pin and if the pin has changed state possibly call an ISR, also changes
   * the mirrored copy of state that is returned for calls to readPin().
   * 
   * If an ISR is attached to this GPIO, call if the speicifed PinStatus matches */
    virtual void refreshState() = 0;

    /** Convience function for the common case of mapping to only one GPIO */
    virtual PinStatus readPin() = 0;

    /** Convience function for the common case of mapping to only one GPIO */
    virtual void writePin(PinStatus s) = 0;

    virtual int analogRead() = 0;

    virtual void analogWrite(int v) = 0;

    virtual void setPinMode(PinMode m) = 0;

    virtual void attachInterrupt(voidFuncPtr callback, PinStatus mode) = 0;

    virtual void detachInterrupt() = 0;
};

/**
 * An implementation of a single GPIO line.  A given implementation subclass might be SimGPIOPin or
 * LinuxGPIOPin etc...
 */
class GPIOPin : public GPIOPinIf
{
    pin_size_t number;
    String name;

    /** The current pinmode, defaults to INPUT_PULLUP to match most hardware */
    PinMode mode = INPUT_PULLUP;

    /** The last read/written value that reflects the current status of the real hardware */
    PinStatus status = HIGH;

    voidFuncPtr isr = NULL;

protected:
    int8_t isrPinStatus = -1; // -1 or PinStatus
public:
    GPIOPin(pin_size_t n, String _name) : number(n), name(_name) {}
    virtual ~GPIOPin() {}

    pin_size_t getPinNum() const { return number; }

    const char *getName() const { return name.c_str(); }

    /** Called to read from a pin and if the pin has changed state possibly call an ISR, also changes
   * the mirrored copy of state that is returned for calls to readPin().
   * 
   * If an ISR is attached to this GPIO, call if the speicifed PinStatus matches */
    void refreshState()
    {
        if (mode != OUTPUT)
        {
            auto newState = readPinHardware();
            auto oldState = status;
            status = newState;
            callISR(oldState, newState);
        }
    }

    /** Convience function for the common case of mapping to only one GPIO */
    virtual PinStatus readPin()
    {
        return status;
    }

    /** Convience function for the common case of mapping to only one GPIO */
    virtual void writePin(PinStatus s)
    {
        status = s;
    }

    virtual int analogRead()
    {
        notImplemented("gpio:analogRead");
        return 4242;
    }

    virtual void analogWrite(int v) NOT_IMPLEMENTED("gpio:refreshState");

    virtual void attachInterrupt(voidFuncPtr callback, PinStatus mode)
    {
        isr = callback;
        isrPinStatus = mode;
    }

    virtual void detachInterrupt()
    {
        isr = NULL;
        isrPinStatus = -1;
    }

    virtual void setPinMode(PinMode m)
    {
        mode = m;
    }

private:
    /** Called by refreshState()
   * 
   * If an ISR is attached to this GPIO, call if the speicifed PinStatus matches */
    void callISR(PinStatus oldState, PinStatus newState)
    {
        auto s = isrPinStatus;
        if ((s == HIGH && newState) ||
            (s == LOW && !newState) ||
            (s == RISING && !oldState && newState) ||
            (s == FALLING && oldState && !newState) ||
            (s == CHANGE && !!oldState != !!newState))
        {
            log(SysGPIO, LogDebug, "GPIOPin::callISR(%s, %d)", getName(), getPinNum());
            assert(isr);
            isr();
        }
    }

protected:
    /// Read the low level hardware for this pin
    virtual PinStatus readPinHardware()
    {
        // default to assume no change
        return status;
    }
};

class SimGPIOPin : public GPIOPin
{
    bool silent = false; // If silent, we won't emit logs

public:
    SimGPIOPin(pin_size_t n, String _name) : GPIOPin(n, _name) {}

    /** Set silent mode
     * @return this for easy chaining
     */
    SimGPIOPin *setSilent(bool s = true)
    {
        silent = s;
        return this;
    }

protected:
    virtual void writePin(PinStatus s)
    {
        if (!silent)
            log(SysGPIO, LogInfo, "SimGPIOPin::writePin(%s, %d, %d)", getName(), getPinNum(), s);
        GPIOPin::writePin(s);
    }

    virtual PinStatus readPin()
    {
        auto r = GPIOPin::readPin();
        if (!silent)
            log(SysGPIO, LogInfo, "SimGPIOPin::readPin(%s, %d, %d)", getName(), getPinNum(), r);
        return r;
    }

    virtual void setPinMode(PinMode m)
    {
        if (!silent)
            log(SysGPIO, LogInfo, "SimGPIOPin::setPinMode(%s, %d, %d)", getName(), getPinNum(), m);
        GPIOPin::setPinMode(m);
    }
};

void gpioInit();
void gpioIdle();

/// Assign an implementation to a specific pin
void gpioBind(GPIOPinIf *p);