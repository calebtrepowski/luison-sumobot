#ifdef TEST_ROBOCLAW
#include <Arduino.h>
#include <RoboClaw.h>
#include "pinNumbers.h"

RoboClaw roboclaw(&Serial1, 10000);

const int address = 0x80;

void setup()
{
    roboclaw.begin(38400);
    roboclaw.ForwardMixed(address, 0);
    roboclaw.TurnRightMixed(address, 0);
    // roboclaw.DutyAccelM1M2
}

void loop()
{
    roboclaw.ForwardMixed(address, 64);
    delay(2000);
    roboclaw.BackwardMixed(address, 64);
    delay(2000);
}

#endif