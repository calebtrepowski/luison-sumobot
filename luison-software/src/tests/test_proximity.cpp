#ifdef TEST_PROXIMITY
#include <Arduino.h>
#include "debugUtils.h"
#include "proximity.h"

void printStates();

void setup()
{
    proximity::setup();
    DEBUG_BEGIN(MONITOR_SPEED);
}

void loop()
{
    // benchmarkFunction(proximity::readStates, 5000000ULL);
    // while (true)
    // {
    // }
    proximity::readStates();
    printStates();
    delay(500);
}

void printStates()
{
    DEBUG_PRINTLN("-----------");
    DEBUG_PRINT(proximity::frontLeft.state);
    DEBUG_PRINT(" ");
    DEBUG_PRINT(proximity::frontCenter.state);
    DEBUG_PRINT(" ");
    DEBUG_PRINTLN(proximity::frontRight.state);

    DEBUG_PRINT(proximity::left.state);
    DEBUG_PRINT("   ");
    DEBUG_PRINTLN(proximity::right.state);

    DEBUG_PRINT("  ");
    DEBUG_PRINTLN(proximity::back.state);
    DEBUG_PRINTLN("-----------");
}

#endif