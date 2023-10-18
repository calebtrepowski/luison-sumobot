#ifdef TEST_MOTOR

#include <Arduino.h>

#include "pinNumbers.h"
#include "motorDriver.h"
#include "debugUtils.h"

void testForward();
void testBack();

void setup()
{
    DEBUG_BEGIN(MONITOR_SPEED);
    DEBUG_PRINTLN(pcTaskGetName(NULL));
    motors::setup();
}

void loop()
{
    motors::goForward(5);
    delay(6000);
    motors::brake();
    delay(3000);
    // testForward();
    // testBack();
}

void testForward()
{
    /* pay attention to speeds */
    motors::goForward(2);
    while (true)
    {
    }
}

void testBack()
{
    /* pay attention to speeds */
    motors::goBack(1);
    while (true)
    {
    }
}

#endif