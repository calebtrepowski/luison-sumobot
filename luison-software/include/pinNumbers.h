#ifndef _pinNumbers_h
#define _pinNumbers_h

#include <Arduino.h>

// Gyroscope
const uint_fast8_t I2C_SCL = 40;
const uint_fast8_t I2C_SDA = 42;

// Kill Switch
const uint_fast8_t KILL_SWITCH_EMERGENCY_STOP = 7;
const uint_fast8_t KILL_SWITCH_START = 8;

// Proximity Sensors
const uint_fast8_t PROXIMITY_LEFT = 46;
const uint_fast8_t PROXIMITY_FRONT_LEFT = 35;
const uint_fast8_t PROXIMITY_FRONT_CENTER = 47;
const uint_fast8_t PROXIMITY_FRONT_RIGHT = 21;
const uint_fast8_t PROXIMITY_RIGHT = 13;
const uint_fast8_t PROXIMITY_BACK = 12;

// Line Sensors
const uint_fast8_t LINE_FRONT_LEFT = 1;
const uint_fast8_t LINE_FRONT_RIGHT = 2;
// const uint_fast8_t LINE_BACK_RIGHT = 4;
// const uint_fast8_t LINE_BACK_LEFT = 5;

const uint_fast8_t LINE_FRONT_LEFT_THRESHOLD_VALUE = 300;
const uint_fast8_t LINE_FRONT_RIGHT_THRESHOLD_VALUE = 300;
const uint_fast8_t LINE_BACK_RIGHT_THRESHOLD_VALUE = 300;
const uint_fast8_t LINE_BACK_LEFT_THRESHOLD_VALUE = 300;

// Dip Switch
const uint_fast8_t DIP_BIT_0 = 37;
const uint_fast8_t DIP_BIT_1 = 41;
const uint_fast8_t DIP_BIT_2 = 38;
const uint_fast8_t DIP_BIT_3 = 39;

// RGB Led
const uint_fast8_t RGB_LED_PIN = 48;

// Aux GPIOs
const uint_fast8_t AUX_PIN_6 = 6;
const uint_fast8_t AUX_PIN_15 = 15;
const uint_fast8_t AUX_PIN_16 = 16;

// Motor
#ifdef DRIVER_ROBOCLAW_SERIAL
const uint_fast8_t MOTOR_TX_PIN = 17;
const uint_fast8_t MOTOR_RX_PIN = 18;

#elif defined(DRIVER_ROBOCLAW_RC)
const uint_fast8_t MOTOR_1_PIN = 17;
const uint_fast8_t MOTOR_2_PIN = 18;

#elif defined(DRIVER_ZEROLAG)
const uint_fast8_t MOTOR_A_PWM = 5;
const uint_fast8_t MOTOR_A_ENABLE = 18;

const uint_fast8_t MOTOR_B_PWM = 16;
const uint_fast8_t MOTOR_B_ENABLE = 4;

#elif defined(DRIVER_MEIMOTOR)
const uint_fast8_t MOTOR_A_PWM = 17;
const uint_fast8_t MOTOR_A_OUTPUT_1 = 6;
const uint_fast8_t MOTOR_A_OUTPUT_2 = 16;

const uint_fast8_t MOTOR_B_PWM = 18;
const uint_fast8_t MOTOR_B_OUTPUT_1 = 15;
const uint_fast8_t MOTOR_B_OUTPUT_2 = 4;
// const uint_fast8_t MOTOR_POWER_SENSOR = 17;
// const uint_fast8_t MOTOR_CURRENT_DETECTION = 15;

#endif

#endif