#ifdef TEST_PROXIMITY
#include <Arduino.h>
#include "debugUtils.h"
#include "proximity.h"
#include "sstream"

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
    std::ostringstream aux;
    aux << "-----------\n";
    aux << proximity::frontLeft.state;
    aux << " ";
    aux << proximity::frontCenter.state;
    aux << " ";
    aux << proximity::frontRight.state;
    aux << "\n";

    aux << proximity::left.state;
    aux << "   ";
    aux << proximity::right.state;
    aux << "\n";

    aux << "  ";
    aux << proximity::back.state;
    aux << "\n-----------";

    DEBUG_PRINTLN(aux.str().data());
}

#endif