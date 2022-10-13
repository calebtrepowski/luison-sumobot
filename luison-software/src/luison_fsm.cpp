#ifdef LUISON_FSM
#include <Arduino.h>

#include "pinNumbers.h"

#include "gyroscope.h"
#include "line.h"

#ifndef DRIVER_ZEROLAG
#include "motor.h"
#else
#include "motorZerolag.h"
#endif

#include "onOffControl.h"
#include "onOffInterruption.h"
#include "proximity.h"
#include "fsm/fsm.h"

// #define DEBUG

void setup()
{
    gyroscope::setup();
    line::setup();
    motors::setup();
    onOffControl::setup();
    proximity::setup();

    onOffInterruption::setOnOffInterruption();
    // attachInterrupt(onOffControl::control.pin, toggleIdleISR, RISING);

    fsm::priorState = NULL;
    fsm::state = fsm::idle;
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("setup");
#endif
}

void loop()
{
    fsm::state();
}

// void attackFront()
// {
//     if (state != priorState)
//     {
// #ifdef DEBUG
//         Serial.println("attack front");
// #endif
//         priorState = state;
//         motors::setSpeedBoth(15U);
//         motors::goForward();
//     }

//     line::readValues();
//     proximity::readStates();

//     if (LINE_FRONT_DETECTED)
//     {
//         state = avoidFallFrontLeft;
//         return;
//     }
// }

// void turnRight()
// {
//     using namespace gyroscope;
//     if (state != priorState)
//     {
// #ifdef DEBUG
//         Serial.println("turn right");
// #endif
//         priorState = state;
//         mpu.update();
//         motors::turnRight();
//         motors::setSpeedBoth(4U);
//         referenceAngleZ = mpu.getAngleZ();
//     }

//     mpu.update();
//     currentAngleZ = mpu.getAngleZ();

//     if (abs(currentAngleZ - referenceAngleZ) > turnAngle)
//     {
//         state = normalSearch;
//     }
// }

// void turnLeft()
// {
//     using namespace gyroscope;
//     if (state != priorState)
//     {
// #ifdef DEBUG
//         Serial.println("turn left");
// #endif
//         priorState = state;
//         mpu.update();
//         motors::turnLeft();
//         motors::setSpeedBoth(4U);
//         referenceAngleZ = mpu.getAngleZ();
//     }

//     mpu.update();
//     currentAngleZ = mpu.getAngleZ();

//     if (abs(currentAngleZ - referenceAngleZ) > turnAngle)
//     {
//         state = normalSearch;
//     }
// }

// void turn45Left()
// {
//     if (innerState != priorInnerState)
//     {
//         motors::turnLeft();
//         motors::setSpeedBoth(5U);
//         priorInnerState = innerState;
//     }
// }

// void diagonalAttack()
// {
//     if (state != priorState)
//     {
// #ifdef DEBUG
//         Serial.println("diagonal attack");
// #endif
//         priorState = state;

//         priorInnerState = NULL;
//         innerState = turn45Left;
//     }

//     innerState();

//     if (LINE_FRONT_DETECTED)
//     {
//         state = avoidFallFrontLeft;
//     }
// }

#endif