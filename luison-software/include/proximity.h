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

#ifdef DEBUG
    void printStates()
    {
        Serial.println("-----------");
        Serial.print(proximity::frontLeft.state);
        Serial.print(" ");
        Serial.print(proximity::frontCenter.state);
        Serial.print(" ");
        Serial.println(proximity::frontRight.state);

        Serial.print(proximity::left.state);
        Serial.print("   ");
        Serial.println(proximity::right.state);

        Serial.print("  ");
        Serial.println(proximity::back.state);
        Serial.println("-----------");
    }
#endif
}

#define OPPONENT_DETECTED_FRONT_LEFT_ONLY proximity::left.state && !proximity::frontLeft.state && proximity::frontCenter.state && proximity::frontRight.state && proximity::right.state && proximity::back.state
#define OPPONENT_DETECTED_FRONT_LEFT_AND_FRONT_CENTER proximity::left.state && !proximity::frontLeft.state && !proximity::frontCenter.state && proximity::frontRight.state && proximity::right.state && proximity::back.state

#define OPPONENT_DETECTED_FRONT_LEFT !proximity::frontLeft.state

#define OPPONENT_DETECTED_FRONT_CENTER_ONLY proximity::left.state &&proximity::frontLeft.state && !proximity::frontCenter.state && proximity::frontRight.state && proximity::right.state && proximity::back.state

#define OPPONENT_DETECTED_FRONT_RIGHT !proximity::frontRight.state
// #define OPPONENT_DETECTED_FRONT_CENTER_AND_FRONT_RIGHT proximity::left.state &&proximity::frontLeft.state && !proximity::frontCenter.state && !proximity::frontRight.state && proximity::right.state && proximity::back.state
// #define OPPONENT_DETECTED_FRONT_RIGHT_ONLY proximity::left.state &&proximity::frontLeft.state && proximity::frontCenter.state && !proximity::frontRight.state && proximity::right.state && proximity::back.state

#define OPPONENT_DETECTED_FRONT_RIGHT_AND_RIGHT proximity::left.state &&proximity::frontLeft.state &&proximity::frontCenter.state && !proximity::frontRight.state && !proximity::right.state && proximity::back.state
#define OPPONENT_DETECTED_RIGHT_ONLY proximity::left.state &&proximity::frontLeft.state &&proximity::frontCenter.state &&proximity::frontRight.state && !proximity::right.state && proximity::back.state
#define OPPONENT_DETECTED_BACK_ONLY proximity::left.state &&proximity::frontLeft.state &&proximity::frontCenter.state &&proximity::frontRight.state &&proximity::right.state && !proximity::back.state
#define OPPONENT_DETECTED_LEFT_ONLY !proximity::left.state &&proximity::frontLeft.state &&proximity::frontCenter.state &&proximity::frontRight.state &&proximity::right.state &&proximity::back.state
#define OPPONENT_DETECTED_LEFT_AND_FRONT_LEFT !proximity::left.state && !proximity::frontLeft.state && proximity::frontCenter.state && proximity::frontRight.state && proximity::right.state && proximity::back.state

#define OPPONENT_NOT_DETECTED_FRONT_CENTER proximity::frontCenter.state
#define OPPONENT_NOT_DETECTED_FRONT_RIGHT proximity::frontRight.state

#endif