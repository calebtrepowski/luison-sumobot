#ifndef _motor_driver_meimotor_h
#define _motor_driver_meimotor_h

#ifdef DRIVER_MEIMOTOR

#include "motorDriver.h"
#include "debugUtils.h"

namespace motors
{
    const uint_fast8_t PWM_FREQUENCY = 60000; // Hz
    const uint_fast8_t RESOLUTION = 4;        // speed will be divided in 2^RESOLUTION parts
    const uint_fast8_t OFFSET = 16;           // 2^RESOLUTION

    const uint_fast8_t MOTOR_A_PWM_CHANNEL = 0;
    const uint_fast8_t MOTOR_B_PWM_CHANNEL = 1;

    const uint_fast8_t STEP_DURATION_MS = 100;

    struct Motor
    {
        uint_fast8_t PWM_channel;
        uint_fast8_t PWM_pin;
        uint_fast8_t OUTPUT_1;
        uint_fast8_t OUTPUT_2;
        int_fast8_t targetSpeed;  // target speed over 2^RESOLUTION steps (sign indicates direction)
        int_fast8_t currentSpeed; // current speed over 2^RESOLUTION steps (sign indicates direction)
        TaskHandle_t updateSpeedHandle;
    } A, B;

    /*
    motor A: right
    motor B: left
    */

#define CORE_0 0

    void motorAUpdateSpeed(void *pvParameters)
    {
        bool increaseSpeed = false;
        uint32_t ulNotificationValue = 0;
        unsigned long currentTime, referenceTime;
        while (true)
        {
            ulNotificationValue = ulTaskNotifyTake(pdTRUE, 0);
            if (ulNotificationValue > 0)
            {
                A.targetSpeed = ulNotificationValue - OFFSET;
                DEBUG_PRINTLN(A.targetSpeed);
                if (A.targetSpeed == 0)
                {
                    DEBUG_PRINTLN("frenando motor A");
                    ledcWrite(A.PWM_channel, 0);
                    A.currentSpeed = 0;
                }
                else if (A.targetSpeed * A.currentSpeed < 0)
                {
                    DEBUG_PRINTLN("cambiando direccion motor A");
                    ledcWrite(A.PWM_channel, 1);
                    A.currentSpeed = A.targetSpeed / abs(A.targetSpeed);
                    increaseSpeed = true;
                    referenceTime = millis();
                }
                else if (abs(A.targetSpeed) < abs(A.currentSpeed))
                {
                    DEBUG_PRINTLN("reduciendo velocidad motor A");
                    ledcWrite(A.PWM_channel, abs(A.targetSpeed));
                    A.currentSpeed = A.targetSpeed;
                }
                else
                {
                    increaseSpeed = true;
                    referenceTime = millis();
                }
            }

            if (increaseSpeed && abs(A.currentSpeed) < abs(A.targetSpeed))
            {
                currentTime = millis();
                if (currentTime - referenceTime > STEP_DURATION_MS)
                {
                    DEBUG_PRINTLN("aumentando velocidad motor A");
                    if (A.targetSpeed < A.currentSpeed)
                    {
                        --A.currentSpeed;
                    }
                    else
                    {
                        ++A.currentSpeed;
                    }
                    DEBUG_PRINTLN(A.currentSpeed);
                    ledcWrite(A.PWM_channel, abs(A.currentSpeed));
                    referenceTime = currentTime;
                }
            }
            else
            {
                increaseSpeed = false;
            }
            vTaskDelay(pdMS_TO_TICKS(1));
        }
    }
    void motorBUpdateSpeed(void *pvParameters)
    {
        bool increaseSpeed = false;
        uint32_t ulNotificationValue = 0;
        unsigned long currentTime, referenceTime;
        while (true)
        {
            ulNotificationValue = ulTaskNotifyTake(pdTRUE, 0);
            if (ulNotificationValue > 0)
            {
                B.targetSpeed = ulNotificationValue - OFFSET;
                DEBUG_PRINTLN(B.targetSpeed);
                if (B.targetSpeed == 0)
                {
                    DEBUG_PRINTLN("frenando motor B");
                    ledcWrite(B.PWM_channel, 0);
                    B.currentSpeed = 0;
                }
                else if (B.targetSpeed * B.currentSpeed < 0)
                {
                    DEBUG_PRINTLN("cambiando direccion motor B");
                    ledcWrite(B.PWM_channel, 1);
                    B.currentSpeed = B.targetSpeed / abs(B.targetSpeed);
                    increaseSpeed = true;
                    referenceTime = millis();
                }
                else if (abs(B.targetSpeed) < abs(B.currentSpeed))
                {
                    DEBUG_PRINTLN("reduciendo velocidad motor B");
                    ledcWrite(B.PWM_channel, abs(B.targetSpeed));
                    B.currentSpeed = B.targetSpeed;
                }
                else
                {
                    increaseSpeed = true;
                    referenceTime = millis();
                }
            }

            if (increaseSpeed && abs(B.currentSpeed) < abs(B.targetSpeed))
            {
                currentTime = millis();
                if (currentTime - referenceTime > STEP_DURATION_MS)
                {
                    DEBUG_PRINTLN("aumentando velocidad motor B");
                    if (B.targetSpeed < B.currentSpeed)
                    {
                        --B.currentSpeed;
                    }
                    else
                    {
                        ++B.currentSpeed;
                    }
                    DEBUG_PRINTLN(B.currentSpeed);
                    ledcWrite(B.PWM_channel, abs(B.currentSpeed));
                    referenceTime = currentTime;
                }
            }
            else
            {
                increaseSpeed = false;
            }
            vTaskDelay(pdMS_TO_TICKS(1));
        }
    }

    void setup()
    {
        A = {
            .PWM_channel = MOTOR_A_PWM_CHANNEL,
            .PWM_pin = MOTOR_A_PWM,
            .OUTPUT_1 = MOTOR_A_OUTPUT_1,
            .OUTPUT_2 = MOTOR_A_OUTPUT_2,
            .targetSpeed = 0,
            .currentSpeed = 0,
            .updateSpeedHandle = nullptr};

        B = {
            .PWM_channel = MOTOR_B_PWM_CHANNEL,
            .PWM_pin = MOTOR_B_PWM,
            .OUTPUT_1 = MOTOR_B_OUTPUT_1,
            .OUTPUT_2 = MOTOR_B_OUTPUT_2,
            .targetSpeed = 0,
            .currentSpeed = 0,
            .updateSpeedHandle = nullptr};

        pinMode(A.OUTPUT_1, OUTPUT);
        pinMode(A.OUTPUT_2, OUTPUT);
        pinMode(B.OUTPUT_1, OUTPUT);
        pinMode(B.OUTPUT_2, OUTPUT);

        ledcSetup(A.PWM_channel, PWM_FREQUENCY, RESOLUTION);
        ledcAttachPin(A.PWM_pin, A.PWM_channel);

        ledcSetup(B.PWM_channel, PWM_FREQUENCY, RESOLUTION);
        ledcAttachPin(B.PWM_pin, B.PWM_channel);

        xTaskCreatePinnedToCore(&motorAUpdateSpeed, "motorAUpdateSpeed", 4096, NULL, 5, &A.updateSpeedHandle, CORE_0);
        xTaskCreatePinnedToCore(&motorBUpdateSpeed, "motorBUpdateSpeed", 4096, NULL, 5, &B.updateSpeedHandle, CORE_0);

        brake();
    }

    void brake()
    {
        DEBUG_PRINTLN("brake");

        digitalWrite(A.OUTPUT_1, LOW);
        digitalWrite(A.OUTPUT_2, LOW);

        digitalWrite(B.OUTPUT_1, LOW);
        digitalWrite(B.OUTPUT_2, LOW);

        xTaskNotify(A.updateSpeedHandle, 0 + OFFSET, eSetValueWithOverwrite);
        xTaskNotify(B.updateSpeedHandle, 0 + OFFSET, eSetValueWithOverwrite);
    }

    void goForward(const uint_fast8_t commonSpeed)
    {
        DEBUG_PRINTLN("go forward common speed");

        digitalWrite(A.OUTPUT_2, LOW);
        digitalWrite(A.OUTPUT_1, HIGH);

        digitalWrite(B.OUTPUT_2, LOW);
        digitalWrite(B.OUTPUT_1, HIGH);

        xTaskNotify(A.updateSpeedHandle, OFFSET + commonSpeed, eSetValueWithOverwrite);
        xTaskNotify(B.updateSpeedHandle, OFFSET + commonSpeed, eSetValueWithOverwrite);
    }

    void goForward(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        // ledcWrite(A.PWM_channel, speedMotorA);
        // ledcWrite(B.PWM_channel, speedMotorB);

        digitalWrite(A.OUTPUT_2, LOW);
        digitalWrite(A.OUTPUT_1, HIGH);

        digitalWrite(B.OUTPUT_2, LOW);
        digitalWrite(B.OUTPUT_1, HIGH);

        xTaskNotify(A.updateSpeedHandle, OFFSET + speedMotorA, eSetValueWithOverwrite);
        xTaskNotify(B.updateSpeedHandle, OFFSET + speedMotorB, eSetValueWithOverwrite);
    }

    void goBack(const uint_fast8_t commonSpeed)
    {
        DEBUG_PRINTLN("go back common speed");

        // ledcWrite(A.PWM_channel, commonSpeed);
        // ledcWrite(B.PWM_channel, commonSpeed);

        digitalWrite(A.OUTPUT_1, LOW);
        digitalWrite(A.OUTPUT_2, HIGH);

        digitalWrite(B.OUTPUT_1, LOW);
        digitalWrite(B.OUTPUT_2, HIGH);

        xTaskNotify(A.updateSpeedHandle, OFFSET - commonSpeed, eSetValueWithOverwrite);
        xTaskNotify(B.updateSpeedHandle, OFFSET - commonSpeed, eSetValueWithOverwrite);
    }

    void goBack(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB)
    {
        digitalWrite(A.OUTPUT_1, LOW);
        digitalWrite(A.OUTPUT_2, HIGH);

        digitalWrite(B.OUTPUT_1, LOW);
        digitalWrite(B.OUTPUT_2, HIGH);

        xTaskNotify(A.updateSpeedHandle, OFFSET - speedMotorA, eSetValueWithOverwrite);
        xTaskNotify(B.updateSpeedHandle, OFFSET - speedMotorB, eSetValueWithOverwrite);
    }

    void turnRight(const uint_fast8_t commonSpeed)
    {
        digitalWrite(A.OUTPUT_2, LOW);
        digitalWrite(A.OUTPUT_1, HIGH);

        digitalWrite(B.OUTPUT_1, LOW);
        digitalWrite(B.OUTPUT_2, HIGH);

        xTaskNotify(A.updateSpeedHandle, OFFSET + commonSpeed, eSetValueWithOverwrite);
        xTaskNotify(B.updateSpeedHandle, OFFSET - commonSpeed, eSetValueWithOverwrite);
    }

    void turnLeft(const uint_fast8_t commonSpeed)
    {
        digitalWrite(A.OUTPUT_1, LOW);
        digitalWrite(A.OUTPUT_2, HIGH);

        digitalWrite(B.OUTPUT_2, LOW);
        digitalWrite(B.OUTPUT_1, HIGH);

        xTaskNotify(A.updateSpeedHandle, OFFSET - commonSpeed, eSetValueWithOverwrite);
        xTaskNotify(B.updateSpeedHandle, OFFSET + commonSpeed, eSetValueWithOverwrite);
    }
}

#endif

#endif