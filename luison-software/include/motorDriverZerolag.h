#ifndef _motor_driver_zerolag_h
#define _motor_driver_zerolag_h

#ifdef DRIVER_ZEROLAG

#include "motorDriver.h"

namespace motors
{
    const uint_fast8_t PWM_FREQUENCY = 40000; // Hz

    /* NO CAMBIAR RESOLUCION, SI ES MÁS DE 4 SE VA A QUEMAR EL DRIVER */
    const uint_fast8_t RESOLUTION = 4; // speed will be divided in 2^RESOLUTION parts

    uint_fast8_t BRAKE_DUTY_CYCLE;

    const uint_fast8_t MOTOR_A_PWM_CHANNEL = 0;
    const uint_fast8_t MOTOR_B_PWM_CHANNEL = 1;

    struct Motor
    {
        uint_fast8_t PWM_channel;
        uint_fast8_t PWM_pin;
        uint_fast8_t enable;
    } A, B;

    void setup()
    {
        BRAKE_DUTY_CYCLE = 1;

        for (uint_fast8_t i = 0; i < RESOLUTION - 1; ++i)
        {
            BRAKE_DUTY_CYCLE *= 2;
        }

        A = {
            .PWM_channel = MOTOR_A_PWM_CHANNEL,
            .PWM_pin = MOTOR_A_PWM,
            .enable = MOTOR_A_ENABLE};

        B = {
            .PWM_channel = MOTOR_B_PWM_CHANNEL,
            .PWM_pin = MOTOR_B_PWM,
            .enable = MOTOR_B_ENABLE};

        pinMode(A.enable, OUTPUT);
        pinMode(B.enable, OUTPUT);

        digitalWrite(A.enable, LOW);
        digitalWrite(B.enable, LOW);

        ledcSetup(A.PWM_channel, PWM_FREQUENCY, RESOLUTION);
        ledcAttachPin(A.PWM_pin, A.PWM_channel);

        ledcSetup(B.PWM_channel, PWM_FREQUENCY, RESOLUTION);
        ledcAttachPin(B.PWM_pin, B.PWM_channel);
    }

    void brake()
    {
        digitalWrite(A.enable, LOW);
        ledcWrite(A.PWM_channel, BRAKE_DUTY_CYCLE);

        digitalWrite(B.enable, LOW);
        ledcWrite(B.PWM_channel, BRAKE_DUTY_CYCLE);
    }

    /**
     * speed: [1, 6]
     */
    void goForward(const uint_fast8_t commonSpeed)
    {
        digitalWrite(A.enable, HIGH);
        ledcWrite(A.PWM_channel, BRAKE_DUTY_CYCLE + commonSpeed);

        digitalWrite(B.enable, HIGH);
        ledcWrite(B.PWM_channel, BRAKE_DUTY_CYCLE + commonSpeed);
    }

    /**
     * speeds: [1, 6]
     */
    void goForward(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        digitalWrite(A.enable, HIGH);
        ledcWrite(A.PWM_channel, BRAKE_DUTY_CYCLE + speedMotorA);

        digitalWrite(B.enable, HIGH);
        ledcWrite(B.PWM_channel, BRAKE_DUTY_CYCLE + speedMotorB);
    }

    /**
     * speed: [1, 6]
     */
    void goBack(const uint_fast8_t commonSpeed)
    {
        digitalWrite(A.enable, HIGH);
        ledcWrite(A.PWM_channel, BRAKE_DUTY_CYCLE - commonSpeed);

        digitalWrite(B.enable, HIGH);
        ledcWrite(B.PWM_channel, BRAKE_DUTY_CYCLE - commonSpeed);
    }

    /**
     * speeds: [1, 6]
     */
    void goBack(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        digitalWrite(A.enable, HIGH);
        ledcWrite(A.PWM_channel, BRAKE_DUTY_CYCLE - speedMotorA);

        digitalWrite(B.enable, HIGH);
        ledcWrite(B.PWM_channel, BRAKE_DUTY_CYCLE - speedMotorB);
    }

    /**
     * speed: [1, 6]
     */
    void turnRight(const uint_fast8_t commonSpeed)
    {
        digitalWrite(A.enable, HIGH);
        ledcWrite(A.PWM_channel, BRAKE_DUTY_CYCLE + commonSpeed);

        digitalWrite(B.enable, HIGH);
        ledcWrite(B.PWM_channel, BRAKE_DUTY_CYCLE - commonSpeed);
    }

    /**
     * speed: [1, 6]
     */
    void turnLeft(const uint_fast8_t commonSpeed)
    {
        digitalWrite(A.enable, HIGH);
        ledcWrite(A.PWM_channel, BRAKE_DUTY_CYCLE - commonSpeed);
        digitalWrite(B.enable, HIGH);
        ledcWrite(B.PWM_channel, BRAKE_DUTY_CYCLE + commonSpeed);
    }

}

#endif

#endif