//
// Created by kevinh on 9/1/20.
//

#include "Arduino.h"

#define TEST_PIN 7

static SPISettings spiSettings(4000000, MSBFIRST, SPI_MODE0);

void setup(void) {
    pinMode(TEST_PIN, OUTPUT);
    digitalWrite(TEST_PIN, LOW);

    SPI.begin();

    SPI.beginTransaction(spiSettings);
    uint8_t testBuf[4];
    SPI.transfer(testBuf, sizeof(testBuf));
    SPI.endTransaction();

    Wire.begin();

    Wire.beginTransmission(0x55);
    Wire.write(5);
    Wire.endTransmission();
}

void loop(void) {
    digitalWrite(TEST_PIN, digitalRead(TEST_PIN) == LOW ? HIGH : LOW);
}