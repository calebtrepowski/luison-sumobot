#ifdef TEST_MOTOR

#include <Arduino.h>

#include "pinNumbers.h"
#include "motorDriver.h"
#include "RGBLed.h"
#include "debugUtils.h"

void testForward();
void testBack();

unsigned long referenceTime, currentTime;

void setup()
{
    DEBUG_BEGIN(MONITOR_SPEED);
    DEBUG_PRINTLN(pcTaskGetName(NULL));
    DEBUG_PRINTLN(uxTaskPriorityGet(NULL));
    motors::setup();
    RGBLed::showYellow();
    delay(10000);
    referenceTime = millis();
    RGBLed::showRed();
}

void loop()
{
    motors::turnRight(5);
    delay(6000);
    motors::brake();
    delay(6000);
}

void testForward()
{
    /* pay attention to speeds */
    motors::goForward(2);
    while (true)
    {
    }
}

#endif