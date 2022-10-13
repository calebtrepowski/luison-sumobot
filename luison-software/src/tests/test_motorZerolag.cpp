#include "pinNumbers.h"

#ifdef DRIVER_ZEROLAG

#ifdef TEST_MOTOR

#include <Arduino.h>
#include "motorZerolag.h"

void testForward();
void testBack();
void testDifferentSpeeds();

void setup()
{
    motors::setup();
}

void loop()
{
    testBack();
}

void testForward()
{
    motors::goForward(1);
    while (true)
    {
    }
}

void testBack()
{
    motors::goBack(1);
    while (true)
    {
    }
}

#endif

#endif