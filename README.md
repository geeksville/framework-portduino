# Portduino

This is an experiment with getting the Arduino API so that it can run on top of the Linux OS.

You don't want this yet ;-)

## Description

Someone wanted Meshtastic for a new linux based tablet, so I'm making a new new thing (which might be useful for other projects).

I'm going to implement the arduino libs/API layer and support the following device level access from (blessed) user-space regular apps:

- SPI
- I2C
- Interrupt handlers (they won't know they are actually in userspace)
- GPIO control
- Serial (but actually being done through any Unix file descriptor - so could be pipes/files/devices)
- Any of the above can be implemented by particular 'Drivers' - so either the mainboard kernel-space SPI/I2C controller or via external USB to SPI/I2C/GPIO adapters

(This is the portion of Arduino that my project needs - and I bet this is sufficient for most Arduino projects)

## Secondary goals

Eventually a variant of this library will allow removing SoftDevice from the NRF52 targets - for a dramatic flash/RAM savings (this will be built on top of [Apache MyNewt](https://mynewt.apache.org/))

## TODO (short term)

- Turn SPI probing on for RF95
- Implement Thread and Lock
- Implement Interrupt dispatching
- Allow multiple GPIO implementations (on a per GPIO basis) - lets user mix and max sim pins, with motherboard pins, with USB pins
- Add platform-arm
- Add CS341SPI driver (USB to SPI chip)
- Implement InterruptHandler via threads
- Have meshtastic talk to radio over that chip

## TODO (long term)

- Change PORTDUINO def to PORTDUINO and PORTDUINO_Linux_x86_64
- Figure out why -Os breaks the executable and what part of platformio is setting that (it comes in before the platform stuff even)
- Change to use platform-native
- Split out threading library from meshtastic
- Implement a tiny rasberry pi example that blinks a LED
- Show that same example blinking a sim LED
- Announce and request feedback
- Use exceptions on linux
- Split out logging library
- Change into an actual real platformio "framework"
- Send in platformio PR
- Let LinuxSerial go places other than stdout
- Make a variant that runs on top of MyNewt
- Unify Thread/Semaphore/TypedQueue wrappers with the FreeRTOS versions

## Done

- DONE Use https://github.com/arduino/ArduinoCore-nRF528x-mbedos as a model?
- DONE Get hello world building as an app
- DONE Add SimGPIO
- DONE Add SimSPI
- DONE Add SimI2C
- DONE Add Serial
- DONE Build and run Meshtastic on top of this new framework (stubbed tho)
- Implement printf
- Implement random
- Implement FS
