#ifndef _lineFollower_h
#define _lineFollower_h
#include <Arduino.h>
#include "pinNumbers.h"

namespace line
{
    struct lineSensor
    {
        uint_fast8_t pin;
        uint_fast8_t value;
        uint_fast8_t referenceValue;
    } frontLeft, frontRight, backRight, backLeft;

    void setup()
    {
        frontLeft.pin = LINE_FRONT_LEFT;
        frontRight.pin = LINE_FRONT_RIGHT;
        backRight.pin = LINE_BACK_RIGHT;
        backLeft.pin = LINE_BACK_LEFT;

        frontLeft.referenceValue = 200;
        frontRight.referenceValue = 200;
        // rightBack.referenceValue = 200;
        // leftBack.referenceValue = 2700;

        pinMode(frontLeft.pin, INPUT);
        pinMode(frontRight.pin, INPUT);
        pinMode(backRight.pin, INPUT);
        pinMode(backLeft.pin, INPUT);
    }

    void readValues()
    {
        frontLeft.value = analogRead(frontLeft.pin);
        frontRight.value = analogRead(frontRight.pin);
        backRight.value = analogRead(backRight.pin);
        backLeft.value = analogRead(backLeft.pin);
    }
}

#define LINE_FRONT_DETECTED line::frontLeft.value < line::frontLeft.referenceValue || line::frontRight.value < line::frontRight.referenceValue
#define LINE_FRONT_LEFT_DETECTED line::frontLeft.value < line::frontLeft.referenceValue
#define LINE_FRONT_RIGHT_DETECTED line::frontRight.value < line::frontRight.referenceValue

#endif