#ifdef TEST_RGB_LED
#include <Arduino.h>
#include <RGBLed.h>
#include "debugUtils.h"


void cycleRGB(uint32_t delayTime);


void setup()
{
}

void loop()
{
    cycleRGB(1000);
}

void cycleRGB(uint32_t delayTime)
{
    using namespace RGBLed;
    showRed();
    delay(delayTime);
    showGreen();
    delay(delayTime);
    showBlue();
    delay(delayTime);
}

#endif