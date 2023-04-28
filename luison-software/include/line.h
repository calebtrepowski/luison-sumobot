#ifndef _lineFollower_h
#define _lineFollower_h
#include <Arduino.h>
#include <driver/adc.h>
#include "esp32-hal-gpio.h"
#include "pinNumbers.h"

namespace line
{
    struct lineSensor
    {
        uint_fast8_t pin;
        adc1_channel_t channel;
        uint_fast8_t value;
        uint_fast8_t thresholdValue;
    } frontLeft, frontRight, backRight, backLeft;

    void setup()
    {
        frontLeft.pin = LINE_FRONT_LEFT;
        frontRight.pin = LINE_FRONT_RIGHT;
        backRight.pin = LINE_BACK_RIGHT;
        backLeft.pin = LINE_BACK_LEFT;

        frontLeft.channel = (adc1_channel_t)digitalPinToAnalogChannel(frontLeft.pin);
        frontRight.channel = (adc1_channel_t)digitalPinToAnalogChannel(frontRight.pin);
        backRight.channel = (adc1_channel_t)digitalPinToAnalogChannel(backRight.pin);
        backLeft.channel = (adc1_channel_t)digitalPinToAnalogChannel(backLeft.pin);

        frontLeft.thresholdValue = LINE_FRONT_LEFT_THRESHOLD_VALUE;
        frontRight.thresholdValue = LINE_FRONT_RIGHT_THRESHOLD_VALUE;
        backRight.thresholdValue = LINE_BACK_RIGHT_THRESHOLD_VALUE;
        backLeft.thresholdValue = LINE_BACK_LEFT_THRESHOLD_VALUE;

        pinMode(frontLeft.pin, ANALOG);
        pinMode(frontRight.pin, ANALOG);
        pinMode(backRight.pin, ANALOG);
        pinMode(backLeft.pin, ANALOG);
    }

    void readValues()
    {
        frontLeft.value = adc1_get_raw(frontLeft.channel);
        frontRight.value = adc1_get_raw(frontRight.channel);
        backRight.value = adc1_get_raw(backRight.channel);
        backLeft.value = adc1_get_raw(backLeft.channel);
    }
}

#define LINE_FRONT_DETECTED line::frontLeft.value < line::frontLeft.referenceValue || line::frontRight.value < line::frontRight.referenceValue
#define LINE_FRONT_LEFT_DETECTED line::frontLeft.value < line::frontLeft.referenceValue
#define LINE_FRONT_RIGHT_DETECTED line::frontRight.value < line::frontRight.referenceValue

#endif