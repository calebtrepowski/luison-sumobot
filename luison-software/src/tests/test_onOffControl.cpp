#ifdef TEST_ON_OFF
#include <Arduino.h>
#include "onOffControl.h"

void setup()
{
    Serial.begin(9600);
    onOffControl::setup();
}

bool state;

void loop()
{
    state = digitalRead(onOffControl::control.pin);
    Serial.println(state);
    // delay(1);
}
#endif