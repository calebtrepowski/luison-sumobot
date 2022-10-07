#ifndef _gyroscope_h
#define _gyroscope_h

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

const uint_fast8_t BUILTIN_LED = 2;

namespace gyroscope
{

    MPU6050 mpu(Wire);

    float referenceAngleZ, currentAngleZ;

    /* 0 if OK */
    byte status;

    void setup()
    {
        pinMode(BUILTIN_LED, OUTPUT);
        digitalWrite(BUILTIN_LED, HIGH);
        Wire.begin();
        status = mpu.begin();
        unsigned char attempts = 0;
        while (status != 0)
        {
            status = mpu.begin();
        }
        digitalWrite(BUILTIN_LED, LOW);
        mpu.calcOffsets(); // gyro and accelero
    }
}

#endif