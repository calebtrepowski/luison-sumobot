#ifndef _fsm_config_values_h_
#define _fsm_config_values_h_

/* Speeds: [1, 6] */

/* Normal search */
#define NORMAL_SEARCH_SPEED 3U

#define ATTACK_FRONT_FULL_GAS_TIME 500  // ms
#define ATTACK_FRONT_LIFT_OFF_TIME 1000 // ms, es acumulado! el tiempo de liftoff es liftofftime - fullgastime
#define ATTACK_FRONT_FULL_GAS_SPEED 6U
#define ATTACK_FRONT_LIFT_OFF_SPEED 4U

#define AIM_FRONT_SIDE_MAX_TURN_DURATION 10U // ms
#define AIM_FRONT_SIDE_TURN_ANGLE 2 * 45     // ° (degrees)

#define AIM_FRONT_SIDE_SPEED_OUTER 6U
#define AIM_FRONT_SIDE_SPEED_INNER 1U

#define AIM_SIDE_MAX_TURN_DURATION 20U // ms
#define AIM_SIDE_TURN_ANGLE 2 * 90      // ° (degrees)
#define AIM_SIDE_SPEED_OUTER 4U
#define AIM_SIDE_SPEED_INNER 1U

#define AVOID_FALL_FRONT_REVERSE_DURATION 115U  // ms
#define AVOID_FALL_FRONT_MAX_TURN_DURATION 135U // ms
#define AVOID_FALL_FRONT_TURN_ANGLE 2 * 30      // ° (degrees)
#define AVOID_FALL_FRONT_REVERSE_SPEED 5U
#define AVOID_FALL_FRONT_TURN_SPEED 5U

#define AIM_BACK_MAX_TURN_DURATION 300U // ms
#define AIM_BACK_TURN_ANGLE 2 * 180     // ° (degrees)
#define AIM_BACK_SPEED_OUTER 4U
#define AIM_BACK_SPEED_INNER 1U

#define DIAGONAL_KICKBACK_MAX_REVERSE_TIME 300U // ms
#define DIAGONAL_KICKBACK_INNER_REVERSE_SPEED 1U
#define DIAGONAL_KICKBACK_OUTER_REVERSE_SPEED 3U

#endif