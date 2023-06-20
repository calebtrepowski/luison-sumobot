#ifndef _motor_driver_roboclaw_h
#define _motor_driver_roboclaw_h

#ifdef DRIVER_ROBOCLAW_SERIAL

#include "motorDriver.h"

#include <Arduino.h>
#include <RoboClaw.h>

namespace motors
{
    const uint_fast8_t ADDRESS = 0x80;
    const uint_fast8_t BAUD_RATE = 38400;
    const uint_fast8_t TIMEOUT = 10000;

    RoboClaw roboclaw(&Serial1, TIMEOUT);

    void setup()
    {
        roboclaw.begin(BAUD_RATE);
        pinMode(KILL_SWITCH_EMERGENCY_STOP, OUTPUT);
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, LOW);
    }

    void brake()
    {
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, LOW);
        roboclaw.ForwardMixed(ADDRESS, 0);
    }

    void goForward(const uint_fast8_t commonSpeed)
    {
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, HIGH);
        roboclaw.ForwardMixed(ADDRESS, commonSpeed);
    }

    void goForward(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, HIGH);
        roboclaw.ForwardM1(ADDRESS, speedMotorA);
        roboclaw.ForwardM2(ADDRESS, speedMotorB);
    }

    void goBack(const uint_fast8_t commonSpeed)
    {
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, HIGH);
        roboclaw.BackwardMixed(ADDRESS, commonSpeed);
    }

    void goBack(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, HIGH);
        roboclaw.BackwardM1(ADDRESS, speedMotorA);
        roboclaw.BackwardM2(ADDRESS, speedMotorB);
    }

    void turnRight(const uint_fast8_t commonSpeed)
    {
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, HIGH);
        roboclaw.ForwardM1(ADDRESS, commonSpeed);
        roboclaw.BackwardM2(ADDRESS, commonSpeed);
    }

    void turnLeft(const uint_fast8_t commonSpeed)
    {
        digitalWrite(KILL_SWITCH_EMERGENCY_STOP, HIGH);
        roboclaw.BackwardM1(ADDRESS, commonSpeed);
        roboclaw.ForwardM2(ADDRESS, commonSpeed);
    }

}

#endif

#endif