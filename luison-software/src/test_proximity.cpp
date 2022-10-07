#ifdef TEST_PROXIMITY
#include <Arduino.h>
#include "proximity.h"

void printStates();

void setup()
{
    proximity::setup();
    Serial.begin(9600);
}

void loop()
{
    proximity::readStates();
    Serial.println("-----------");
    printStates();
    Serial.println("-----------");
    delay(500);
}

void printStates()
{
    Serial.print(proximity::frontLeft.state);
    Serial.print(" ");
    Serial.print(proximity::frontCenter.state);
    Serial.print(" ");
    Serial.println(proximity::frontRight.state);

    Serial.print(proximity::left.state);
    Serial.print("   ");
    Serial.println(proximity::right.state);

    Serial.print("  ");
    Serial.println(proximity::back.state);
}

#endif