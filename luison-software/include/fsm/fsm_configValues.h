#ifndef _fsm_config_values_h_
#define _fsm_config_values_h_

/* Speeds
0: brake
15: max speed (because motors::resolution is set to 4)
*/

#define NORMAL_SEARCH_SPEED 13U
#define ATTACK_FRONT_SPEED 15U

#define AIM_FRONT_SIDE_MAX_TURN_DURATION 50U // ms
#define AIM_FRONT_SIDE_TURN_ANGLE 2 * 45     // ° (degrees)

// Estos dos juntos no tienen que sumar más de 15
#define AIM_FRONT_SIDE_SPEED_OUTER 13U
#define AIM_FRONT_SIDE_SPEED_INNER 6U

#define AIM_SIDE_MAX_TURN_DURATION 150U // ms
#define AIM_SIDE_TURN_ANGLE 2 * 90      // ° (degrees)
#define AIM_SIDE_SPEED_OUTER 13U
#define AIM_SIDE_SPEED_INNER 2U

#endif