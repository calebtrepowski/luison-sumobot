#ifdef LUISON_FSM
#include <Arduino.h>

#include "gyroscope.h"
#include "line.h"
#include "motor.h"
#include "onOffControl.h"
#include "onOffInterruption.h"
#include "proximity.h"

typedef void (*STATE_HANDLER_T)();

void idle();
void avoidFallFront();
void attackFront();
void normalOperation();
void turnRight();
void turnLeft();

volatile STATE_HANDLER_T prior_state, state;
uint_fast32_t avoidFallFrontTime, avoidFallFrontReverseTime;
uint_fast8_t turnAngle;

/* INTERRUPTION */
uint_fast32_t buttonTime = 0;
uint_fast32_t lastButtonTime = 0;
uint_fast32_t lastOnTime = 0;

const uint_fast8_t debounceTime = 10;   // ms
const uint_fast8_t minimumOnTime = 500; // ms

uint_fast8_t strategy = 0;

void IRAM_ATTR toggleIdleISR()
{
    buttonTime = millis();
    if (buttonTime - lastButtonTime > debounceTime)
    {
        if (buttonTime - lastOnTime > minimumOnTime)
        {
            // minimumOnTime es para que no se apague si el arbitro mantiene apretado

            if (state == idle)
            {
                strategy = dipSwitch::readInt();
                state = normalOperation;
                lastOnTime = buttonTime;
            }
            else
            {
                state = idle;
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

    // prior_state = states::NONE;
    // state = states::IDLE;
    prior_state = NULL;
    state = idle;
#ifdef DEBUG
    Serial.begin(9600);
#endif
}

void loop()
{
    state();
}

void idle()
{
    if (state != prior_state)
    {
#ifdef DEBUG
        Serial.println("idle");
#endif
        prior_state = state;
        motors::brake();
        motors::setSpeedBoth(0U);
    }
}

void avoidFallFront()
{
    uint_fast32_t t;

    if (state != prior_state)
    {
#ifdef DEBUG
        Serial.println("avoid fall front");
#endif
        prior_state = state;
        avoidFallFrontTime = millis();
        motors::setSpeedBoth(4U);
        motors::goBack();

        // if (LINE_FRONT_LEFT_DETECTED)
        // {
        //     turnAngle = 90;
        //     next_state =
        // }
    }

    t = millis();

    // if (t - avoidFallFrontTime > 500)
    // {
    //     if state
    //         = turn90Right;
    // }
}

void attackFront()
{
    if (state != prior_state)
    {
#ifdef DEBUG
        Serial.println("attack front");
#endif
        prior_state = state;
        motors::setSpeedBoth(15U);
        motors::goForward();
    }

    line::readValues();
    proximity::readStates();

    if (LINE_FRONT_DETECTED)
    {
        state = avoidFallFront;
        return;
    }
    
}

void normalOperation()
{
    if (state != prior_state)
    {
#ifdef DEBUG
        Serial.println("normal operation");
#endif
        prior_state = state;
        motors::setSpeedBoth(4U);
        motors::goForward();
    }

    line::readValues();
    if (LINE_FRONT_DETECTED)
    {
        // state = avoidFallFront;
        turnAngle = 90;
        state = turnLeft;
        return;
    }

    proximity::readStates();
    if (OPPONENT_DETECTED_FRONT_CENTER_ONLY){

    }
    if (OPPONENT_DETECTED_BACK_ONLY)
    {
        turnAngle = 180;
        state = turnLeft;
        return;
    }
}

void turnRight()
{
    using namespace gyroscope;
    if (state != prior_state)
    {
#ifdef DEBUG
        Serial.println("turn right");
#endif
        prior_state = state;
        mpu.update();
        motors::turnRight();
        motors::setSpeedBoth(4U);
        referenceAngleZ = mpu.getAngleZ();
    }

    mpu.update();
    currentAngleZ = mpu.getAngleZ();

    if (abs(currentAngleZ - referenceAngleZ) > turnAngle)
    {
        state = normalOperation;
    }
}

void turnLeft()
{
    using namespace gyroscope;
    if (state != prior_state)
    {
#ifdef DEBUG
        Serial.println("turn left");
#endif
        prior_state = state;
        mpu.update();
        motors::turnLeft();
        motors::setSpeedBoth(4U);
        referenceAngleZ = mpu.getAngleZ();
    }

    mpu.update();
    currentAngleZ = mpu.getAngleZ();

    if (abs(currentAngleZ - referenceAngleZ) > turnAngle)
    {
        state = normalOperation;
    }
}

#endif