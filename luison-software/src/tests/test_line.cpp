#ifdef TEST_LINE
#include <Arduino.h>
#include "line.h"
#include "bluetooth.h"

void printValues();
void printValuesBT();

void setup()
{
    line::setup();
    Serial.begin(9600);
    bluetooth::setup();
}

void loop()
{
    line::readValues();
    Serial.println("-----------");
    printValuesBT();
    Serial.println("-----------");
    delay(500);
}

void printValues()
{
    Serial.print(line::frontLeft.value);
    Serial.print("\t");
    Serial.println(line::frontRight.value);
    // Serial.print(line::backLeft.value);
    // Serial.print("\t");
    // Serial.print(line::backRight.value);
    Serial.println();
}
void printValuesBT()
{
    using namespace bluetooth;
    SerialBT.print(line::frontLeft.value);
    SerialBT.print("\t");
    SerialBT.println(line::frontRight.value);
    SerialBT.print(line::backLeft.value);
    SerialBT.print("\t");
    SerialBT.print(line::backRight.value);
    SerialBT.println();
}
#endif