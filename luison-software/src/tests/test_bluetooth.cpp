#ifdef TEST_BLUETOOTH
#include <Arduino.h>
#include "bluetooth.h"

void setup()
{
    bluetooth::setup();
}

void loop()
{
    bluetooth::echo();
}
#endif