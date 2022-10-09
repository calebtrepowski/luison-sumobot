#ifdef TEST_GYRO

#define TEST_GYROSCOPE
#ifdef TEST_GYROSCOPE
#include "Wire.h"
#include <MPU6050_light.h>
#include "gyroscope.h"

// float referenceAngleZ, angleZ;

void setup()
{
    gyroscope::setup();
    Serial.begin(115200);
}
void loop()
{
    using namespace gyroscope;
    mpu.update();
    referenceAngleZ = mpu.getAngleZ();

    while (true)
    {
        if (status == 0)
        {
            mpu.update();
            Serial.println(mpu.getAngleZ());
            delay(100);
        }
        else
        {
            Serial.println("no entro");
            gyroscope::setup();
        }
    }
}
#endif
#endif