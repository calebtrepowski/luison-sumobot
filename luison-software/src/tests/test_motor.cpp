#ifdef TEST_MOTOR

#include <Arduino.h>
#include "motor.h"

void testCurrentDetection();
void testForwardBack();

void setup()
{
    motors::setup();
    motors::setSpeedBoth(4U);
}

void loop()
{
    // testCurrentDetection();
    testForwardBack();
    // motors::goForward();
    // while (true)
    // {
    // }
    // delay(1000);
    // motors::brake();
    // delay(200);
    // motors::goBack();
    // delay(1000);
    // motors::brake();
    // delay(200);
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