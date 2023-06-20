#ifdef TEST_MOTOR

#include <Arduino.h>

#include "pinNumbers.h"
#include "motorDriver.h"

void testForward();
void testBack();

void setup()
{
    motors::setup();
}

void loop()
{
    testForward();
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