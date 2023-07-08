#ifdef TEST_ON_OFF
#include <Arduino.h>
#include "pinNumbers.h"
// #include "onOffControl.h"

void setup()
{
    Serial.begin(MONITOR_SPEED);
    pinMode(LINE_BACK_RIGHT, INPUT_PULLUP);
    // onOffControl::setup();
}

bool state;

void loop()
{
    state = digitalRead(LINE_BACK_RIGHT);
    Serial.println(state);
    delay(200);
}
#endif