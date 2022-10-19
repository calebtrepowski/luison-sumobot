#ifndef _fsm_config_values_h_
#define _fsm_config_values_h_

/* Speeds: [1, 6] */

/* Normal search */
#define NORMAL_SEARCH_SPEED 1U

#define ATTACK_FRONT_SPEED 2U
#define ATTACK_FRONT_FULL_GAS_TIME 500  // ms
#define ATTACK_FRONT_LIFT_OFF_TIME 1000 // ms, es acumulado! el tiempo de liftoff es liftofftime - fullgastime
#define ATTACK_FRONT_FULL_GAS_SPEED 6U
#define ATTACK_FRONT_LIFT_OFF_SPEED 4U

#define AIM_FRONT_SIDE_MAX_TURN_DURATION 50U // ms
#define AIM_FRONT_SIDE_TURN_ANGLE 2 * 45     // ° (degrees)

#define AIM_FRONT_SIDE_SPEED_OUTER 2U
#define AIM_FRONT_SIDE_SPEED_INNER 1U

#define AIM_SIDE_MAX_TURN_DURATION 150U // ms
#define AIM_SIDE_TURN_ANGLE 2 * 90      // ° (degrees)
#define AIM_SIDE_SPEED_OUTER 2U
#define AIM_SIDE_SPEED_INNER 1U

#define AVOID_FALL_FRONT_REVERSE_DURATION 300U  // ms
#define AVOID_FALL_FRONT_MAX_TURN_DURATION 500U // ms
#define AVOID_FALL_FRONT_TURN_ANGLE 2 * 30      // ° (degrees)
#define AVOID_FALL_FRONT_REVERSE_SPEED 1U
#define AVOID_FALL_FRONT_TURN_SPEED 1U

#define AIM_BACK_GO_FRONT_DURATION 300U // ms
#define AIM_BACK_MAX_TURN_DURATION 500U // ms
#define AIM_BACK_TURN_ANGLE 2 * 180     // ° (degrees)
#define AIM_BACK_GO_FRONT_SPEED 1U
#define AIM_BACK_TURN_SPEED 1U

#endif