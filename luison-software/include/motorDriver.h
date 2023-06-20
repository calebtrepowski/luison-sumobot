#ifndef _motor_driver_h_
#define _motor_driver_h_

#include <Arduino.h>
#include "pinNumbers.h"

namespace motors
{
    void setup();
    void brake();
    void goForward(const uint_fast8_t commonSpeed);
    void goForward(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB);
    void goBack(const uint_fast8_t commonSpeed);
    void goBack(const uint_fast8_t speedMotorA, const uint_fast8_t speedMotorB);
    void turnRight(const uint_fast8_t commonSpeed);
    void turnLeft(const uint_fast8_t commonSpeed);
}

/*
for some reason linker doesn't find function
definitions if files are not included explicitly
*/
#include "motorDriverMeimotor.h"
#include "motorDriverZerolag.h"
#include "motorDriverRoboclawSerial.h"
#include "motorDriverRoboclawRC.h"

#endif