#ifndef _pinNumbers_h
#define _pinNumbers_h

#include <Arduino.h>

// Gyroscope
const uint_fast8_t GYROSCOPE_SCL = 22;
const uint_fast8_t GYROSCOPE_SDA = 21;

// Start button/control
const uint_fast8_t ON_OFF_CONTROL = 23;
// const uint_fast8_t ON_OFF_CONTROL = 14;

// Proximity Sensors
const uint_fast8_t PROXIMITY_LEFT = 33;
const uint_fast8_t PROXIMITY_FRONT_LEFT = 32;
const uint_fast8_t PROXIMITY_FRONT_CENTER = 35;
const uint_fast8_t PROXIMITY_FRONT_RIGHT = 34;
const uint_fast8_t PROXIMITY_RIGHT = 39;
const uint_fast8_t PROXIMITY_BACK = 36;

// Line Sensors
/* front left y front right están intercambiados
respecto al esquemático */
const uint_fast8_t LINE_FRONT_LEFT = 12;
const uint_fast8_t LINE_FRONT_RIGHT = 13;
// const uint_fast8_t LINE_BACK_RIGHT = 23;
const uint_fast8_t LINE_BACK_RIGHT = 27;
const uint_fast8_t LINE_BACK_LEFT = 14;
// const uint_fast8_t LINE_BACK_LEFT = 27;

// Dip Switch
const uint_fast8_t DIP_BIT_0 = 26;
const uint_fast8_t DIP_BIT_1 = 25;

// Motor
const uint_fast8_t MOTOR_A_PWM = 5;
const uint_fast8_t MOTOR_A_OUTPUT_1 = 18;
const uint_fast8_t MOTOR_A_OUTPUT_2 = 19;

const uint_fast8_t MOTOR_B_PWM = 16;
const uint_fast8_t MOTOR_B_OUTPUT_1 = 4;
const uint_fast8_t MOTOR_B_OUTPUT_2 = 2;

// const uint_fast8_t MOTOR_POWER_SENSOR = 17;
const uint_fast8_t MOTOR_CURRENT_DETECTION = 15;


#endif