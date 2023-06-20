#ifdef TEST_ROBOCLAW
#include <Arduino.h>
#include <ESP32Servo.h>
#include "pinNumbers.h"

Servo servo1, servo2;

void setup()
{
    servo1.attach(17);
    servo2.attach(18);
}

void loop()
{
    servo1.writeMicroseconds(1520);
    servo2.writeMicroseconds(1520);
    delay(1000);
    servo1.writeMicroseconds(1600);
    servo2.writeMicroseconds(1600);
    delay(1000);
}


#endif