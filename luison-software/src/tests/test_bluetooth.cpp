#ifdef TEST_BLUETOOTH
#include <Arduino.h>
#include "bluetooth.h"

uint_fast8_t active;

void setup()
{
    bluetooth::setup();
}

void loop()
{
    // bluetooth::echo();
    if (!active)
    {
        bluetooth::sendData(std::string("Idle\n"));
    }
    if (bluetooth::loadStart(active))
    {
        bluetooth::sendData(std::string("Estado inicial\n"));
    }
    delay(100);
}


#endif