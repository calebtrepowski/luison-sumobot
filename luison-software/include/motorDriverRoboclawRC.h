#ifndef _motor_driver_roboclaw_rc_h
#define _motor_driver_roboclaw_rc_h

#ifdef DRIVER_ROBOCLAW_RC

#include "motorDriver.h"

#include <Arduino.h>
#include <ESP32Servo.h>
#include "pinNumbers.h"

namespace motors
{
    Servo leftMotor, rightMotor;
    const int BRAKE_PULSE_DURATION = 1520;
    const int FULL_REVERSE_PULSE_DURATION = 1120;
    const int FULL_FORWARD_PULSE_DURATION = 1920;

    const int RESOLUTION_NUMBER_STEPS = 6;

    void setup()
    {
        leftMotor.attach(MOTOR_1_PIN);
        rightMotor.attach(MOTOR_2_PIN);
        brake();
    }

    void brake()
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION);
    }

    /* speed: 0-RESOLUTION_NUMBER_STEPS */
    void goForward(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
    }

    /* speed: 0-RESOLUTION_NUMBER_STEPS */
    void goForward(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION + speedMotorA * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION + speedMotorB * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
    }

    void goBack(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
    }
    void goBack(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION - speedMotorA * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION - speedMotorB * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
    }
    void turnLeft(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
    }
    void turnRight(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / RESOLUTION_NUMBER_STEPS);
    }
}

#endif
#endif