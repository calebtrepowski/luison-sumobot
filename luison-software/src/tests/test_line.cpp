#ifdef TEST_LINE
#include <Arduino.h>
#include "line.h"
#include "debugUtils.h"

void printValues();

void setup()
{
    line::setup();
    DEBUG_BEGIN(MONITOR_SPEED);
    benchmarkFunction<void>(line::readValues, 500000ULL);
}

void loop()
{
    line::readValues();
    printValues();
    delay(500);
}

void printValues()
{
    DEBUG_PRINT(line::frontLeft.value);
    DEBUG_PRINT("\t");
    DEBUG_PRINTLN(line::frontRight.value);
    DEBUG_PRINT(line::backLeft.value);
    DEBUG_PRINT("\t");
    DEBUG_PRINT(line::backRight.value);
    DEBUG_PRINTLN("\n");
}
#endif