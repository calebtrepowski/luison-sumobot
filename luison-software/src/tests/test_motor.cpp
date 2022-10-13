#include "pinNumbers.h"

#ifndef DRIVER_ZEROLAG

#ifdef TEST_MOTOR

#include <Arduino.h>
#include "motor.h"

void testCurrentDetection();
void testForwardBack();
void testDifferentSpeeds();

void setup()
{
    motors::setup();
    // motors::setSpeedBoth(4U);
}

void loop()
{
    // testCurrentDetection();
    // testForwardBack();
    testDifferentSpeeds();
}

void testCurrentDetection()
{
    Serial.begin(9600);
    motors::goForward();
    while (true)
    {
        Serial.println(analogRead(MOTOR_CURRENT_DETECTION));
    }
}

void testForwardBack()
{
    while (true)
    {
        motors::goForward();
        delay(1500);
        motors::brake();
        delay(500);
        motors::goBack();
        delay(1500);
        motors::brake();
        delay(500);
    }
}

#endif

#endif