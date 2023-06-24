#ifndef _gyroscope_h
#define _gyroscope_h

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

#include "pinNumbers.h"
#include "RGBLed.h"

namespace gyroscope
{

    MPU6050 mpu(Wire);

    int GYRO_CONFIG_NUM = 3;
    int ACC_CONFIG_NUM = 2;

    float referenceAngleZ, currentAngleZ;

    /* 0 if OK */
    byte status = -1;

    void setup()
    {
        RGBLed::showBlue();
        delay(500);

        Wire.begin(I2C_SDA, I2C_SCL, 1000001UL);

        for (u_int8_t i = 0; i < 10; i++)
        {
            status = mpu.begin(GYRO_CONFIG_NUM, ACC_CONFIG_NUM);
        }

        if (status == 0)
        {
            RGBLed::showGreen();
        }
        else
        {
            RGBLed::showYellow();
        }

        mpu.calcOffsets();
    }

    float getAngleZ(void)
    {
        return mpu.getAngleZ();
    }
}

#endif