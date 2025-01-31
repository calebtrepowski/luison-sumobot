#ifdef TEST_LINE
#include <Arduino.h>
#include <sstream>
#include "line.h"
#include "debugUtils.h"

void printValues();

void setup()
{
    line::setup();
    DEBUG_BEGIN(MONITOR_SPEED);
    // benchmarkFunction<void>(line::readValues, 500000ULL);
}

void loop()
{
    line::readValues();
    printValues();
    delay(500);
}

void printValues()
{
    std::ostringstream aux;
    aux << "-----------\n";
    aux << line::frontLeft.value;
    aux << "\t";
    aux << line::frontRight.value;
    aux << "\n";
    aux << line::backLeft.value;
    aux << "\t";
    aux << line::backRight.value;
    aux << "\n-----------";

    DEBUG_PRINTLN(aux.str().data());
    // DEBUG_PRINT(line::frontLeft.value);
    // DEBUG_PRINT("\t");
    // DEBUG_PRINTLN(line::frontRight.value);
    // DEBUG_PRINT(line::backLeft.value);
    // DEBUG_PRINT("\t");
    // DEBUG_PRINT(line::backRight.value);
    // DEBUG_PRINTLN("\n");
}
#endif