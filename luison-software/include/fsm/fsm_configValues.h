#ifndef _fsm_config_values_h_
#define _fsm_config_values_h_

/* Speeds: [1, 6] */

#ifndef WOOD_RING
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
#define AIM_SIDE_TURN_ANGLE 2 * 90     // ° (degrees)
#define AIM_SIDE_SPEED_OUTER 6U
#define AIM_SIDE_SPEED_INNER 1U

#define AVOID_FALL_FRONT_REVERSE_DURATION 115U  // ms
#define AVOID_FALL_FRONT_MAX_TURN_DURATION 135U // ms
#define AVOID_FALL_FRONT_TURN_ANGLE 2 * 30      // ° (degrees)
#define AVOID_FALL_FRONT_REVERSE_SPEED 6U
#define AVOID_FALL_FRONT_TURN_SPEED 6U

#define AIM_BACK_MAX_TURN_DURATION 300U // ms
#define AIM_BACK_TURN_ANGLE 2 * 180     // ° (degrees)
#define AIM_BACK_SPEED_OUTER 6U
#define AIM_BACK_SPEED_INNER 1U

#define DIAGONAL_KICKBACK_MAX_REVERSE_TIME 300U // ms
#define DIAGONAL_KICKBACK_INNER_REVERSE_SPEED 1U
#define DIAGONAL_KICKBACK_OUTER_REVERSE_SPEED 3U

#define DIAGONAL_ATTACK_MOVE_FORWARD_SPEED 6U
#define DIAGONAL_ATTACK_MOVE_FORWARD_DURATION 200U
#define DIAGONAL_ATTACK_TURN_AIM_SPEED_OUTER 6U
#define DIAGONAL_ATTACK_TURN_AIM_SPEED_INNER 1U
#define DIAGONAL_ATTACK_TURN_AIM_DURATION 150U

#define WAIT_SENSORS_MOVE_FORWARD_SPEED 6U
#define WAIT_SENSORS_MOVE_FORWARD_DURATION 50U // ms
#define WAIT_SENSORS_WAIT_MAX_DURATION 3000U

#else
#define NORMAL_SEARCH_SPEED 2U

#define ATTACK_FRONT_FULL_GAS_TIME 500  // ms
#define ATTACK_FRONT_LIFT_OFF_TIME 1000 // ms, es acumulado! el tiempo de liftoff es liftofftime - fullgastime
#define ATTACK_FRONT_FULL_GAS_SPEED 6U
#define ATTACK_FRONT_LIFT_OFF_SPEED 4U

#define AIM_FRONT_SIDE_MAX_TURN_DURATION 10U // ms
#define AIM_FRONT_SIDE_TURN_ANGLE 2 * 45     // ° (degrees)

#define AIM_FRONT_SIDE_SPEED_OUTER 3U
#define AIM_FRONT_SIDE_SPEED_INNER 1U

#define AIM_SIDE_MAX_TURN_DURATION 20U // ms
#define AIM_SIDE_TURN_ANGLE 2 * 90     // ° (degrees)
#define AIM_SIDE_SPEED_OUTER 2U
#define AIM_SIDE_SPEED_INNER 1U

#define AVOID_FALL_FRONT_REVERSE_DURATION 275U  // ms
#define AVOID_FALL_FRONT_MAX_TURN_DURATION 225U // ms
#define AVOID_FALL_FRONT_TURN_ANGLE 2 * 30      // ° (degrees)
#define AVOID_FALL_FRONT_REVERSE_SPEED 2U
#define AVOID_FALL_FRONT_TURN_SPEED 2U

#define AIM_BACK_MAX_TURN_DURATION 300U // ms
#define AIM_BACK_TURN_ANGLE 2 * 180     // ° (degrees)
#define AIM_BACK_SPEED_OUTER 4U
#define AIM_BACK_SPEED_INNER 1U

#define DIAGONAL_KICKBACK_MAX_REVERSE_TIME 300U // ms
#define DIAGONAL_KICKBACK_INNER_REVERSE_SPEED 1U
#define DIAGONAL_KICKBACK_OUTER_REVERSE_SPEED 3U

#define DIAGONAL_ATTACK_MOVE_FORWARD_SPEED 2U
#define DIAGONAL_ATTACK_MOVE_FORWARD_DURATION 800U
#define DIAGONAL_ATTACK_TURN_AIM_SPEED_OUTER 3U
#define DIAGONAL_ATTACK_TURN_AIM_SPEED_INNER 1U
#define DIAGONAL_ATTACK_TURN_AIM_DURATION 120U

#define WAIT_SENSORS_MOVE_FORWARD_SPEED 2U
#define WAIT_SENSORS_MOVE_FORWARD_DURATION 100U // ms
#define WAIT_SENSORS_WAIT_MAX_DURATION 1000U

#endif
#endif