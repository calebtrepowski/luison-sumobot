#ifndef _proximity_h
#define _proximity_h
#include <Arduino.h>
#include "pinNumbers.h"

namespace proximity
{
    struct ProximitySensor
    {
        uint_fast8_t pin;
        uint_fast8_t state;
    } left, frontLeft, frontCenter, frontRight, right, back;

    void setup()
    {
        left.pin = PROXIMITY_LEFT;
        frontLeft.pin = PROXIMITY_FRONT_LEFT;
        frontCenter.pin = PROXIMITY_FRONT_CENTER;
        frontRight.pin = PROXIMITY_FRONT_RIGHT;
        right.pin = PROXIMITY_RIGHT;
        back.pin = PROXIMITY_BACK;

        pinMode(left.pin, INPUT);
        pinMode(frontLeft.pin, INPUT);
        pinMode(frontCenter.pin, INPUT);
        pinMode(frontRight.pin, INPUT);
        pinMode(right.pin, INPUT);
        pinMode(back.pin, INPUT);
    }

    void readStates()
    {
        left.state = digitalRead(left.pin);
        frontLeft.state = digitalRead(frontLeft.pin);
        frontCenter.state = digitalRead(frontCenter.pin);
        frontRight.state = digitalRead(frontRight.pin);
        right.state = digitalRead(right.pin);
        back.state = digitalRead(back.pin);
    }
}

#endif