#ifdef LUISON_FSM
#include <Arduino.h>

#include "gyroscope.h"
#include "line.h"
#include "motor.h"
#include "onOffControl.h"
#include "onOffInterruption.h"
#include "proximity.h"
#include "fsm.h"

// #define DEBUG

/* INTERRUPTION */
uint_fast32_t buttonTime = 0UL;
uint_fast32_t lastButtonTime = 0UL;
uint_fast32_t lastOnTime = 0UL;
uint_fast32_t lastOffTime = 0UL;

const uint_fast8_t debounceTime = 30;     // ms
const uint_fast8_t minimumOnTime = 500;   // ms
const uint_fast8_t minimumOffTime = 3000; // ms

uint_fast8_t initialStrategy = 0;

void IRAM_ATTR toggleIdleISR()
{
    buttonTime = millis();
    if (buttonTime - lastButtonTime > debounceTime)
    {
        if (fsm::state == fsm::idle)
        {
            if (buttonTime - lastOnTime > minimumOffTime || lastOnTime == 0)
            {
                // minimumOnTime es para que no se apague si el arbitro mantiene apretado

                initialStrategy = dipSwitch::readInt();
                switch (initialStrategy)
                {
                // case 1:
                //     state = diagonalAttack;
                //     break;
                // case 2:
                //     state = diagonalKickBack;
                //     break;
                // case 3:
                // break;
                default:
                    fsm::state = fsm::normalSearch;
                    break;
                }

                lastOffTime = buttonTime;
            }
        }
        else
        {
            if (buttonTime - lastOffTime > minimumOnTime)
            {
                fsm::state = fsm::idle;
                lastOnTime = buttonTime;
            }
        }
    }

    lastButtonTime = buttonTime;
}

void setup()
{
    gyroscope::setup();
    line::setup();
    motors::setup();
    onOffControl::setup();
    proximity::setup();
    attachInterrupt(onOffControl::control.pin, toggleIdleISR, RISING);

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