#ifdef TEST_DIP_SWITCH
#include <Arduino.h>
#include "dipSwitch.h"

void setup()
{
    Serial.begin(9600);
    dipSwitch::setup();
}

void loop()
{
    Serial.println(dipSwitch::readInt());
    delay(100);
}
#endif