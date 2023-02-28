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

        pinMode(left.pin, INPUT_PULLUP);
        pinMode(frontLeft.pin, INPUT_PULLUP);
        pinMode(frontCenter.pin, INPUT_PULLUP);
        pinMode(frontRight.pin, INPUT_PULLUP);
        pinMode(right.pin, INPUT_PULLUP);
        pinMode(back.pin, INPUT_PULLUP);
    }

    inline void readStates()
    {      
        left.state = (GPIO.in >> left.pin) & 0x1;
        frontLeft.state = (GPIO.in >> frontLeft.pin) & 0x1;
        frontCenter.state = (GPIO.in >> frontCenter.pin) & 0x1;
        frontRight.state = (GPIO.in1.val >> frontRight.pin) & 0x1;
        right.state = (GPIO.in1.val >> right.pin) & 0x1;
        back.state = (GPIO.in1.val >> back.pin) & 0x1;
    }
}

#define OPPONENT_DETECTED_FRONT_LEFT !proximity::frontLeft.state
#define OPPONENT_DETECTED_FRONT_LEFT_AND_FRONT_CENTER !proximity::frontLeft.state && !proximity::frontCenter.state && proximity::frontRight.state
#define OPPONENT_DETECTED_FRONT_CENTER_ONLY proximity::frontLeft.state && !proximity::frontCenter.state && proximity::frontRight.state
#define OPPONENT_DETECTED_FRONT_CENTER_AND_FRONT_RIGHT proximity::frontLeft.state && !proximity::frontCenter.state && !proximity::frontRight.state
#define OPPONENT_DETECTED_FRONT_RIGHT !proximity::frontRight.state
#define OPPONENT_DETECTED_RIGHT !proximity::right.state
#define OPPONENT_DETECTED_BACK !proximity::back.state
#define OPPONENT_DETECTED_LEFT !proximity::left.state

#define OPPONENT_NOT_DETECTED_FRONT_CENTER proximity::frontCenter.state
#define OPPONENT_NOT_DETECTED_FRONT_RIGHT proximity::frontRight.state
#define OPPONENT_NOT_DETECTED_FRONT_LEFT proximity::frontLeft.state

#endif