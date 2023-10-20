#ifndef _fsm_config_values_h_
#define _fsm_config_values_h_

namespace fsm
{
    struct ConfigValues
    {
        int normalInitialSearchSpeed;
        int normalInitialSearchDuration;
        int normalSearchSpeed;

        int attackFrontFullGasTime; // ms
        int attackFrontLiftOffTime; // ms
        int attackFrontFullGasSpeed;
        int attackFrontLiftOffSpeed;

        int aimFrontSideMaxTurnDuration; // ms
        int aimFrontSideSpeedOuter;
        int aimFrontSideSpeedInner;

        int aimSideMaxTurnDuration; // ms
        int aimSideSpeedOuter;
        int aimSideSpeedInner;

        int avoidFallFrontReverseDuration; // ms
        int avoidFallFrontMaxTurnDuration; // ms
        int avoidFallFrontReverseSpeed;
        int avoidFallFrontTurnSpeed;

        int diagonalAttackMoveForwardSpeed;
        int diagonalAttackMoveForwardDuration; // ms
        int diagonalTurnAimSpeedOuter;
        int diagonalTurnAimSpeedInner;
        int diagonalTurnAimDuration; // ms

        int waitSensorsMoveForwardSpeed;
        int waitSensorsMoveForwardDuration; // ms
        int waitSensorsWaitMaxDuration;     // ms

        int avoidBackTurnSpeed;
        int avoidBackMaxTurnDuration; // ms

        int avoidBackInJInnerSpeed;
        int avoidBackInJOuterSpeed;
        int avoidBackInJMaxTurnDuration;

        int avoidBackInJFrontInnerSpeed;
        int avoidBackInJFrontOuterSpeed;
        int avoidBackInJFrontMaxTurnDuration;

        int bulletSpeed;
    } metalRing, woodRing;

    void initializeValues(void)
    {
        metalRing = {
            .normalInitialSearchSpeed = 5,
            .normalInitialSearchDuration = 50,
            .normalSearchSpeed = 8,

            .attackFrontFullGasTime = 500,
            .attackFrontLiftOffTime = 1000,
            .attackFrontFullGasSpeed = 14,
            .attackFrontLiftOffSpeed = 12,

            .aimFrontSideMaxTurnDuration = 100,
            .aimFrontSideSpeedOuter = 10,
            .aimFrontSideSpeedInner = 6,

            .aimSideMaxTurnDuration = 100,
            .aimSideSpeedOuter = 10,
            .aimSideSpeedInner = 4,

            .avoidFallFrontReverseDuration = 200,
            .avoidFallFrontMaxTurnDuration = 50,
            .avoidFallFrontReverseSpeed = 8,
            .avoidFallFrontTurnSpeed = 8,

            .diagonalAttackMoveForwardSpeed = 11,
            .diagonalAttackMoveForwardDuration = 200,
            .diagonalTurnAimSpeedOuter = 11,
            .diagonalTurnAimSpeedInner = 6,
            .diagonalTurnAimDuration = 150,

            .waitSensorsMoveForwardSpeed = 11,
            .waitSensorsMoveForwardDuration = 200,
            .waitSensorsWaitMaxDuration = 2000,

            .avoidBackTurnSpeed = 6,
            .avoidBackMaxTurnDuration = 225,

            .avoidBackInJInnerSpeed = 6,
            .avoidBackInJOuterSpeed = 2,
            .avoidBackInJMaxTurnDuration = 300,

            .avoidBackInJFrontInnerSpeed = 6,
            .avoidBackInJFrontOuterSpeed = 2,
            .avoidBackInJFrontMaxTurnDuration = 300,

            .bulletSpeed = 14};

        woodRing = {
            .normalInitialSearchSpeed = 2,
            .normalInitialSearchDuration = 10,
            .normalSearchSpeed = 4,

            .attackFrontFullGasTime = 500,
            .attackFrontLiftOffTime = 1000,
            .attackFrontFullGasSpeed = 6,
            .attackFrontLiftOffSpeed = 4,

            .aimFrontSideMaxTurnDuration = 10,
            .aimFrontSideSpeedOuter = 3,
            .aimFrontSideSpeedInner = 1,

            .aimSideMaxTurnDuration = 20,
            .aimSideSpeedOuter = 2,
            .aimSideSpeedInner = 1,

            .avoidFallFrontReverseDuration = 275,
            .avoidFallFrontMaxTurnDuration = 225,
            .avoidFallFrontReverseSpeed = 2,
            .avoidFallFrontTurnSpeed = 2,

            .diagonalAttackMoveForwardSpeed = 2,
            .diagonalAttackMoveForwardDuration = 800,
            .diagonalTurnAimSpeedOuter = 3,
            .diagonalTurnAimSpeedInner = 1,
            .diagonalTurnAimDuration = 120,

            .waitSensorsMoveForwardSpeed = 2,
            .waitSensorsMoveForwardDuration = 100,
            .waitSensorsWaitMaxDuration = 1000,

            .avoidBackTurnSpeed = 6,
            .avoidBackMaxTurnDuration = 200};
    }
}

/* Speeds: [1, 6] */
#endif