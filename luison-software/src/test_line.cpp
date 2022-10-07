#ifdef TEST_LINE
#include <Arduino.h>
#include "line.h"

void printValues();

void setup()
{
    line::setup();
    Serial.begin(9600);
}

void loop()
{
    line::readValues();
    Serial.println("-----------");
    printValues();
    Serial.println("-----------");
    delay(500);
}

void printValues()
{
    Serial.print(line::frontLeft.value);
    Serial.print("\t");
    Serial.println(line::frontRight.value);
    Serial.print(line::backLeft.value);
    Serial.print("\t");
    Serial.print(line::backRight.value);
    Serial.println();
}
#endif