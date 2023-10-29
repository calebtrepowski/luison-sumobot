#ifdef TEST_ALL
#include <Arduino.h>
#include "menu/menuDabbleTerminal.hpp"
#include "menu/calibrationMenu.hpp"

#include "bluetooth.h"
#include "dipSwitch.h"
#include "RGBLed.h"
#include "onOffKillSwitch.h"

/* fsm already includes line, proximity, motor and gyro */
#include "fsm/fsm.h"

MenuDabbleTerminal menu;
CalibrationMenu calibrationMenu, calibrationMenu2;

void fsmSetup();
void fsmAction();
void fsmCleanup();

unsigned long referenceTime;
void printReadingsSetup();

void printLineReadings();
void printProximityReadings();

void printDipSwitchReading();

void calibrateValue1();
void calibrateValue2();

bool onlyFSM;

void setup()
{
    dipSwitch::setup();
    fsm::setup();

    onlyFSM = dipSwitch::readInt() != 9;

    if (!onlyFSM)
    {

        bluetooth::setup();

        // push button for start routine

        menu.addOption("FSM", fsmSetup, fsmAction, fsmCleanup);
        // menu.addOption(
        // "Elegir metal", []()
        // { fsm::configValues = &fsm::metalRing;Terminal.println("Metal elegido!"); },
        // nullptr, nullptr);
        menu.addOption("Sensores de linea", printReadingsSetup, printLineReadings, nullptr);
        // menu.addOption("Sensores de proximidad", printReadingsSetup, printProximityReadings, nullptr);
        menu.addOption(
            "Motores: adelante", []()
            { motors::goForward(fsm::configValues->normalSearchSpeed); },
            []() {}, motors::brake);
        // menu.addOption(
        //     "Motores: atras", []()
        //     { motors::goBack(3); },
        //     []() {}, motors::brake);
        // menu.addOption(
        //     "Motores: izquierda", []()
        //     { motors::turnLeft(3); },
        //     []() {}, motors::brake);
        // menu.addOption(
        //     "Motores: derecha", []()
        //     { motors::turnRight(3); },
        //     []() {}, motors::brake);
        // menu.addOption("Dip Switch", printReadingsSetup, printDipSwitchReading, nullptr);
        menu.addOption("Calibrar parámetro", calibrateValue1, nullptr, nullptr);
        menu.addOption("Calibrar parámetro 2", calibrateValue2, nullptr, nullptr);
        calibrationMenu.addField("step time [ms]", &motors::STEP_DURATION_MS);

        calibrationMenu.addField("Norm srch speed [1-14]", &fsm::configValues->normalSearchSpeed);
        // calibrationMenu.addField("Norm srch init speed [1-6]", &fsm::configValues->normalInitialSearchSpeed);
        // calibrationMenu.addField("Norm srch init dur [ms]", &fsm::configValues->normalInitialSearchDuration);

        /* Avoid fall */
        calibrationMenu.addField("av fall: rev dur [ms]", &fsm::configValues->avoidFallFrontReverseDuration);
        calibrationMenu.addField("av fall: rev speed [1-14]", &fsm::configValues->avoidFallFrontReverseSpeed);
        calibrationMenu.addField("av fall: turn dur [ms]", &fsm::configValues->avoidFallFrontMaxTurnDuration);
        calibrationMenu.addField("av fall: turn speed [1-14]", &fsm::configValues->avoidFallFrontTurnSpeed);

        /* Aim front side */
        // calibrationMenu.addField("aim fs: trn spd in [1-14]", &fsm::configValues->aimFrontSideSpeedInner);
        calibrationMenu.addField("aim fs: trn spd out [1-14]", &fsm::configValues->aimFrontSideSpeedOuter);
        calibrationMenu.addField("aim fs: trn dur  [ms]", &fsm::configValues->aimFrontSideMaxTurnDuration);

        /* Aim side */
        calibrationMenu2.addField("aim s: trn spd  [1-14]", &fsm::configValues->aimSideSpeedOuter);
        calibrationMenu2.addField("aim s: trn dur  [ms]", &fsm::configValues->aimSideMaxTurnDuration);

        /* Attack front */
        calibrationMenu2.addField("AF: full gas speed [1-14]", &fsm::configValues->attackFrontFullGasSpeed);
        // calibrationMenu.addField("AF: full gas time [ms]", &attackFront_fsm::fullGasTime);
        // calibrationMenu.addField("AF: lift off speed [1-6]", &attackFront_fsm::liftOffSpeed);
        // calibrationMenu.addField("AF: lift off time [ms]", &attackFront_fsm::liftOffTime);

        /* Diagonal Attack */
        // calibrationMenu.addField("DA: forward speed [1-6]", &fsm::configValues->diagonalAttackMoveForwardSpeed);
        // calibrationMenu.addField("DA: forward duration [ms]", &fsm::configValues->diagonalAttackMoveForwardDuration);
        // calibrationMenu.addField("DA: turn speed outer [1-6]", &fsm::configValues->diagonalTurnAimSpeedOuter);
        // calibrationMenu.addField("DA: turn speed inner [1-6]", &fsm::configValues->diagonalTurnAimSpeedInner);
        // calibrationMenu.addField("DA: turn duration [ms]", &fsm::configValues->diagonalTurnAimDuration);

        /* Wait sensors */
        calibrationMenu2.addField("WS: forward speed [1-14]", &fsm::configValues->waitSensorsMoveForwardSpeed);
        calibrationMenu2.addField("WS: forward duration [ms]", &fsm::configValues->waitSensorsMoveForwardDuration);
        calibrationMenu2.addField("WS: wait duration [ms]", &fsm::configValues->waitSensorsWaitMaxDuration);

        /* Avoid back */
        // calibrationMenu.addField("av bck: trn spd [1-6]", &fsm::configValues->avoidBackTurnSpeed);
        // calibrationMenu.addField("av bck: trn drtn [ms]", &fsm::configValues->avoidBackMaxTurnDuration);

        /* Avoid back in J*/
        // calibrationMenu.addField("av bck J: trn spd innr [1-6]", &fsm::configValues->avoidBackInJInnerSpeed);
        // calibrationMenu.addField("av bck J: trn spd outr [1-6]", &fsm::configValues->avoidBackInJOuterSpeed);
        // calibrationMenu.addField("av bck J: trn drtn [ms]", &fsm::configValues->avoidBackInJMaxTurnDuration);

        /* Avoid Bullet */
        // calibrationMenu.addField("AB: tr spd [1-14]", &fsm::configValues->avoidBulletTurnRightSpeed);
        // calibrationMenu.addField("AB: tr dur [ms]", &fsm::configValues->avoidBulletTurnRightDuration);
        // calibrationMenu.addField("AB: gf spd [1-14]", &fsm::configValues->avoidBulletGoForwardSpeed);
        // calibrationMenu.addField("AB: gf dur [ms]", &fsm::configValues->avoidBulletGoForwardDuration);
        // calibrationMenu.addField("AB: tl spd [1-14]", &fsm::configValues->avoidBulletTurnLeftSpeed);
        // calibrationMenu.addField("AB: tl dur [ms]", &fsm::configValues->avoidBulletTurnLeftDuration);
    }
}

void loop(void)
{
    if (onlyFSM)
    {
        fsmSetup();
        while (digitalRead(KILL_SWITCH_START))
        {
            fsmAction();
            vTaskDelay(1);
        }
        fsmCleanup();
    }
    else
    {
        RGBLed::showGreen();
        while (true)
        {
            menu.run();
            vTaskDelay(1);
        }
    }
}

void fsmSetup()
{
    pinMode(KILL_SWITCH_START, INPUT_PULLDOWN);
    RGBLed::showYellow();
    while (!digitalRead(KILL_SWITCH_START))
    {
        vTaskDelay(1);
    }
    int initialStrategy = dipSwitch::readInt();
    fsm::initialAction(initialStrategy);
    RGBLed::showRed();
}

void fsmAction()
{
    // if (digitalRead(KILL_SWITCH_START))
    // {
    fsm::state();
    // }
    // else
    // {
    //     fsm::cleanupAction();
    //     RGBLed::showGreen();
    //     while (true)
    //     {
    //     }
    // }
}

void fsmCleanup()
{
    fsm::priorState = NULL;
    fsm::state = fsm::idle;
    fsm::state();
    RGBLed::showYellow();
}
void printReadingsSetup()
{
    referenceTime = millis();
}

void printLineReadings()
{
    if (millis() % referenceTime > 500)
    {
        line::readValues();
        Terminal.println(line::valuesToString());
    }
}

void printProximityReadings()
{
    if (millis() % referenceTime > 500)
    {
        proximity::readStates();
        Terminal.println(proximity::valuesToString());
    }
}

void printDipSwitchReading()
{
    if (millis() % referenceTime > 2000)
    {
        Terminal.println(dipSwitch::readInt());
    }
}

void calibrateValue1()
{
    Terminal.println(calibrationMenu.getFields());

    while (true)
    {
        Dabble.processInput();
        if (Terminal.available())
            break;
    }

    int fieldNumber = Terminal.readString().toInt();
    if (fieldNumber <= 0 || fieldNumber > calibrationMenu.getFieldCount())
    {
        Terminal.println("Asignacion cancelada.");
        return;
    }

    Terminal.println("Ingresar nuevo valor");

    while (true)
    {
        Dabble.processInput();
        if (Terminal.available())
            break;
    }

    int newValue = Terminal.readString().toInt();
    calibrationMenu.updateField(fieldNumber - 1, newValue);

    Terminal.println("Asignacion correcta");
}
void calibrateValue2()
{
    Terminal.println(calibrationMenu2.getFields());

    while (true)
    {
        Dabble.processInput();
        if (Terminal.available())
            break;
    }

    int fieldNumber = Terminal.readString().toInt();
    if (fieldNumber <= 0 || fieldNumber > calibrationMenu2.getFieldCount())
    {
        Terminal.println("Asignacion cancelada.");
        return;
    }

    Terminal.println("Ingresar nuevo valor");

    while (true)
    {
        Dabble.processInput();
        if (Terminal.available())
            break;
    }

    int newValue = Terminal.readString().toInt();
    calibrationMenu2.updateField(fieldNumber - 1, newValue);

    Terminal.println("Asignacion correcta");
}
#endif