#ifndef _fsm_config_values_h_
#define _fsm_config_values_h_

namespace fsm
{
    struct ConfigValues
    {
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

        int avoidBackInnerSpeed;
        int avoidBackOuterSpeed;
        int avoidBackMaxDuration; // ms
    } metalRing, woodRing;

    void initializeValues(void)
    {
        metalRing = {
            .normalSearchSpeed = 3,

            .attackFrontFullGasTime = 500,
            .attackFrontLiftOffTime = 1000,
            .attackFrontFullGasSpeed = 6,
            .attackFrontLiftOffSpeed = 4,

            .aimFrontSideMaxTurnDuration = 10,
            .aimFrontSideSpeedOuter = 6,
            .aimFrontSideSpeedInner = 1,

            .aimSideMaxTurnDuration = 20,
            .aimSideSpeedOuter = 6,
            .aimSideSpeedInner = 1,

            .avoidFallFrontReverseDuration = 115,
            .avoidFallFrontMaxTurnDuration = 135,
            .avoidFallFrontReverseSpeed = 6,
            .avoidFallFrontTurnSpeed = 6,

            .diagonalAttackMoveForwardSpeed = 6,
            .diagonalAttackMoveForwardDuration = 200,
            .diagonalTurnAimSpeedOuter = 6,
            .diagonalTurnAimSpeedInner = 1,
            .diagonalTurnAimDuration = 150,

            .waitSensorsMoveForwardSpeed = 6,
            .waitSensorsMoveForwardDuration = 50,
            .waitSensorsWaitMaxDuration = 3000,

            .avoidBackInnerSpeed = 1,
            .avoidBackOuterSpeed = 6,
            .avoidBackMaxDuration = 500};

        woodRing = {
            .normalSearchSpeed = 2,

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

            .avoidBackInnerSpeed = 1,
            .avoidBackOuterSpeed = 3,
            .avoidBackMaxDuration = 500};
    }
}

/* Speeds: [1, 6] */
#endif