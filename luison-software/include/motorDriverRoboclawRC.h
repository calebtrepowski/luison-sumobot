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

    /* speed: 0-4 */
    void goForward(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / 4);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / 4);
    }

    /* speed: 0-4 */
    void goForward(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION + speedMotorA * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / 4);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION + speedMotorB * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / 4);
    }

    void goBack(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / 4);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / 4);
    }
    void goBack(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION - speedMotorA * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / 4);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION - speedMotorB * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / 4);
    }
    void turnRight(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / 4);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / 4);
    }
    void turnLeft(const uint_fast8_t commonSpeed)
    {
        leftMotor.writeMicroseconds(BRAKE_PULSE_DURATION + commonSpeed * (FULL_FORWARD_PULSE_DURATION - BRAKE_PULSE_DURATION) / 4);
        rightMotor.writeMicroseconds(BRAKE_PULSE_DURATION - commonSpeed * (BRAKE_PULSE_DURATION - FULL_REVERSE_PULSE_DURATION) / 4);
    }
}

#endif
#endif