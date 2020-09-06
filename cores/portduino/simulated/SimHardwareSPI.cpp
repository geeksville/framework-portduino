//
// Created by kevinh on 9/1/20.
//

#include "HardwareSPI.h"
#include "Utility.h"

namespace arduino {

uint8_t HardwareSPI::transfer(uint8_t data) {
  notImplemented("transfer");
  return 0;
}

uint16_t HardwareSPI::transfer16(uint16_t data) {
  notImplemented("transfer16");
  return 0;
}

void HardwareSPI::transfer(void *buf, size_t count)
    NOT_IMPLEMENTED("transferBuf");

// Transaction Functions
void HardwareSPI::usingInterrupt(int interruptNumber)
    NOT_IMPLEMENTED("usingInterrupt");

void HardwareSPI::notUsingInterrupt(int interruptNumber)
    NOT_IMPLEMENTED("notUsingInterrupt");

void HardwareSPI::beginTransaction(SPISettings settings)
    NOT_IMPLEMENTED("beginTransaction");

void HardwareSPI::endTransaction(void) NOT_IMPLEMENTED("endTransaction");

// SPI Configuration methods
void HardwareSPI::attachInterrupt() NOT_IMPLEMENTED("attachInterrupt");

void HardwareSPI::detachInterrupt() NOT_IMPLEMENTED("detachInterrupt");

void HardwareSPI::begin() NOT_IMPLEMENTED("spibegin");

void HardwareSPI::end() NOT_IMPLEMENTED("end");

} // namespace arduino

HardwareSPI SPI;
