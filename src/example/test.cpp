//
// Created by kevinh on 9/1/20.
//

#include "Arduino.h"

#define TEST_PIN 7

void setup(void) {
    pinMode(TEST_PIN, OUTPUT);
    digitalWrite(TEST_PIN, LOW);
}

void loop(void) {
    digitalWrite(TEST_PIN, digitalRead(TEST_PIN) == LOW ? HIGH : LOW);
}