#ifndef _motor_h
#define _motor_h
#include <Arduino.h>
#include "pinNumbers.h"

namespace motors
{
    const uint_fast8_t PWM_FREQUENCY = 60000; // Hz
    const uint_fast8_t RESOLUTION = 4;        // speed will be divided in 2^RESOLUTION parts
    // const uint_fast8_t maxStep = 8;           //

    const uint_fast8_t MOTOR_A_PWM_CHANNEL = 0;
    const uint_fast8_t MOTOR_B_PWM_CHANNEL = 1;

    struct Motor
    {
        uint_fast8_t PWM_channel;
        uint_fast8_t PWM_pin;
        uint_fast8_t OUTPUT_1;
        uint_fast8_t OUTPUT_2;
    } A, B;

    void brake();

    void setup()
    {
        A = {
            .PWM_channel = MOTOR_A_PWM_CHANNEL,
            .PWM_pin = MOTOR_A_PWM,
            .OUTPUT_1 = MOTOR_A_OUTPUT_1,
            .OUTPUT_2 = MOTOR_A_OUTPUT_2};

        B = {
            .PWM_channel = MOTOR_A_PWM_CHANNEL,
            .PWM_pin = MOTOR_B_PWM,
            .OUTPUT_1 = MOTOR_B_OUTPUT_1,
            .OUTPUT_2 = MOTOR_B_OUTPUT_2};

        pinMode(A.OUTPUT_1, OUTPUT);
        pinMode(A.OUTPUT_2, OUTPUT);
        pinMode(B.OUTPUT_1, OUTPUT);
        pinMode(B.OUTPUT_2, OUTPUT);

        brake();

        ledcSetup(A.PWM_channel, PWM_FREQUENCY, RESOLUTION);
        ledcAttachPin(A.PWM_pin, A.PWM_channel);

        ledcSetup(B.PWM_channel, PWM_FREQUENCY, RESOLUTION);
        ledcAttachPin(B.PWM_pin, B.PWM_channel);

        ledcWrite(A.PWM_channel, 0);
        ledcWrite(B.PWM_channel, 0);

        pinMode(MOTOR_CURRENT_DETECTION, INPUT);
    }

    void brake()
    {
        digitalWrite(A.OUTPUT_1, LOW);
        digitalWrite(A.OUTPUT_2, LOW);

        digitalWrite(B.OUTPUT_1, LOW);
        digitalWrite(B.OUTPUT_2, LOW);
    }

    void goForward()
    {
        digitalWrite(A.OUTPUT_1, LOW);
        digitalWrite(A.OUTPUT_2, HIGH);

        digitalWrite(B.OUTPUT_1, LOW);
        digitalWrite(B.OUTPUT_2, HIGH);
    }

    void goBack()
    {
        digitalWrite(A.OUTPUT_2, LOW);
        digitalWrite(A.OUTPUT_1, HIGH);

        digitalWrite(B.OUTPUT_2, LOW);
        digitalWrite(B.OUTPUT_1, HIGH);
    }

    void setSpeedBoth(const uint_fast8_t speed)
    {
        ledcWrite(A.PWM_channel, speed);
        ledcWrite(B.PWM_channel, speed);
    }

}

#endif