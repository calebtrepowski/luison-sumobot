#ifdef TEST_GYRO

#define TEST_GYROSCOPE
#ifdef TEST_GYROSCOPE
#include "Wire.h"
#include "gyroscope.h"
#include "debugUtils.h"

void getAngleZ();
void getAccelerationXYZ();

unsigned long referenceTime, currentTime;
float angleZ;

void setup()
{
    DEBUG_BEGIN(MONITOR_SPEED);
    gyroscope::setup();
    // benchmarkFunction<void>(getAngleZ_benchmark, (uint64_t)100000);

    referenceTime = micros();
}

void loop()
{
    getAngleZ();
    currentTime = micros();
    if (currentTime - referenceTime > 500)
    {
        DEBUG_PRINTLN(angleZ);
    }

    // getAccelerationXYZ();
}

void getAngleZ()
{
    using namespace gyroscope;
    mpu.updateAngleZ();
    angleZ = mpu.getAngleZ();
}

void getAccelerationXYZ()
{
    using namespace gyroscope;

    while (true)
    {
        mpu.update();
        DEBUG_PRINT(mpu.getAccX());
        DEBUG_PRINT("\t");
        DEBUG_PRINT(mpu.getAccY());
        DEBUG_PRINT("\t");
        DEBUG_PRINTLN(mpu.getAccZ());
        delay(100);
    }
}

#endif
#endif