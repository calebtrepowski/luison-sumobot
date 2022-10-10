#ifdef LUISON_FSM
#include <Arduino.h>

#include "gyroscope.h"
#include "line.h"
#include "motor.h"
#include "onOffControl.h"
#include "onOffInterruption.h"
#include "proximity.h"
// #include "fsm.h"

//#define DEBUG

typedef void (*STATE_HANDLER_T)();
typedef void (*INNER_STATE_HANDLER_T)();

void idle();
void avoidFallFrontLeft();
void avoidFallFrontRight();
void attackFront();
void normalSearch();
void turnRight();
void turnLeft();

/* initial strategies */
void diagonalAttack();
void diagonalKickBack();

volatile STATE_HANDLER_T priorState, state;
volatile INNER_STATE_HANDLER_T priorInnerState, innerState;

uint_fast8_t turnAngle;

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
        if (state == idle)
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
                    state = normalSearch;
                    break;
                }

                lastOffTime = buttonTime;
            }
        }
        else
        {
            if (buttonTime - lastOffTime > minimumOnTime)
            {
                state = idle;
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

    priorState = NULL;
    state = idle;
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("setup");
#endif
}

void loop()
{
    state();
}

void idle()
{
    if (state != priorState)
    {
#ifdef DEBUG
        Serial.println("idle");
#endif
        priorState = state;
        motors::brake();
        motors::setSpeedBoth(0U);
    }
}

namespace avoidFallFrontLeft_np
{
    const uint_fast8_t reverseDuration = 300U;  // ms
    const uint_fast8_t maxTurnDuration = 1000U; // ms
    uint_fast32_t t;

    const uint_fast8_t turnAngle = 120; // °
    uint_fast32_t referenceTime;

    const uint_fast8_t reverseSpeed = 3U; // ms
    const uint_fast8_t turnSpeed = 3U;    // ms

    void reverse();
    void turnRight();

    void reverse()
    {
        if (innerState != priorInnerState)
        {
#ifdef DEBUG
            Serial.println("reverse");
#endif
            priorInnerState = innerState;
            referenceTime = millis();
            motors::setSpeedBoth(reverseSpeed);
            motors::goBack();
        }

        t = millis();

        if (t - referenceTime > reverseDuration)
        {
            innerState = turnRight;
        }
    }

    void turnRight()
    {
        using namespace gyroscope;
        if (innerState != priorInnerState)
        {
#ifdef DEBUG
            Serial.println("turn right");
#endif
            priorInnerState = innerState;
            mpu.update();
            motors::setSpeedBoth(turnSpeed);
            motors::turnRight();
            referenceAngleZ = mpu.getAngleZ();
            referenceTime = millis();
        }

        mpu.update();
        currentAngleZ = mpu.getAngleZ();
        t = millis();

        if (abs(currentAngleZ - referenceAngleZ) > turnAngle || t - referenceTime > maxTurnDuration)
        {
            innerState = NULL;
        }
    }
}

void avoidFallFrontLeft()
{

    if (state != priorState)
    {
#ifdef DEBUG
        Serial.println("avoid fall front");
#endif
        priorState = state;

        priorInnerState = NULL;
        innerState = avoidFallFrontLeft_np::reverse;
    }

    if (innerState != NULL)
    {
        innerState();
        return;
    }

    state = normalSearch;
}

namespace avoidFallFrontRight_np
{
    const uint_fast8_t reverseDuration = 300U;  // ms
    const uint_fast8_t maxTurnDuration = 1000U; // ms
    uint_fast32_t t;

    const uint_fast8_t turnAngle = 120; // °
    uint_fast32_t referenceTime;

    const uint_fast8_t reverseSpeed = 3U; // ms
    const uint_fast8_t turnSpeed = 3U;    // ms

    void reverse();
    void turnLeft();

    void reverse()
    {
        if (innerState != priorInnerState)
        {
#ifdef DEBUG
            Serial.println("reverse");
#endif
            priorInnerState = innerState;
            referenceTime = millis();
            motors::setSpeedBoth(reverseSpeed);
            motors::goBack();
        }

        t = millis();

        if (t - referenceTime > reverseDuration)
        {
            innerState = turnLeft;
        }
    }

    void turnLeft()
    {
        using namespace gyroscope;
        if (innerState != priorInnerState)
        {
#ifdef DEBUG
            Serial.println("turn left");
#endif
            priorInnerState = innerState;
            mpu.update();
            motors::setSpeedBoth(turnSpeed);
            motors::turnLeft();
            referenceAngleZ = mpu.getAngleZ();
            referenceTime = millis();
        }

        mpu.update();
        currentAngleZ = mpu.getAngleZ();
        t = millis();

        if (abs(currentAngleZ - referenceAngleZ) > turnAngle || t - referenceTime > maxTurnDuration)
        {
            innerState = NULL;
        }
    }
}

void avoidFallFrontRight()
{

    if (state != priorState)
    {
#ifdef DEBUG
        Serial.println("avoid fall front");
#endif
        priorState = state;

        priorInnerState = NULL;
        innerState = avoidFallFrontRight_np::reverse;
    }

    if (innerState != NULL)
    {
        innerState();
        return;
    }

    state = normalSearch;
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

const uint_fast8_t normalSearchSpeed = 3U;
void normalSearch()
{
    if (state != priorState)
    {
#ifdef DEBUG
        Serial.println("normal operation");
#endif
        priorState = state;
        motors::setSpeedBoth(normalSearchSpeed);
        motors::goForward();
    }

    line::readValues();

    if (LINE_FRONT_LEFT_DETECTED)
    {
        state = avoidFallFrontLeft;
        return;
    }
    
    if (LINE_FRONT_RIGHT_DETECTED)
    {
        state = avoidFallFrontRight;
        return;
    }

    // proximity::readStates();
    // if (OPPONENT_DETECTED_FRONT_CENTER_ONLY)
    // {
    // }
    // if (OPPONENT_DETECTED_BACK_ONLY)
    // {
    //     turnAngle = 180;
    //     state = turnLeft;
    //     return;
    // }
}

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