//
// Created by kevinh on 9/1/20.
//

#include "HardwareSPI.h"
#include "Utility.h"
#include "logging.h"

namespace arduino {

uint8_t HardwareSPI::transfer(uint8_t data) {
  int v = 42;
  log(SysSPI, LogVerbose, "SIM: spiTransfer(%d) -> %d", data, v);
  return v;
}

uint16_t HardwareSPI::transfer16(uint16_t data) {
  int v = 4242;
  log(SysSPI, LogVerbose, "SIM: spiTransfer16(%d) -> %d", data, v);
  return v;
}

void HardwareSPI::transfer(void *buf, size_t count)
    NOT_IMPLEMENTED("transferBuf");

// Transaction Functions
void HardwareSPI::usingInterrupt(int interruptNumber)
    NOT_IMPLEMENTED("spiusingInterrupt");

void HardwareSPI::notUsingInterrupt(int interruptNumber)
    NOT_IMPLEMENTED("spinotUsingInterrupt");

void HardwareSPI::beginTransaction(SPISettings settings) {
  // FIXME implement
}

void HardwareSPI::endTransaction(void) {
  // FIXME implement
}

// SPI Configuration methods
void HardwareSPI::attachInterrupt() NOT_IMPLEMENTED("attachInterrupt");

void HardwareSPI::detachInterrupt() NOT_IMPLEMENTED("detachInterrupt");

void HardwareSPI::begin() {
  // FIXME implement
}

void HardwareSPI::end() {
  // FIXME implement
}

} // namespace arduino

HardwareSPI SPI;
