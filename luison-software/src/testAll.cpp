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
CalibrationMenu calibrationMenu;

void fsmSetup();
void fsmAction();
void fsmCleanup();

unsigned long referenceTime;
void printReadingsSetup();

void printLineReadings();
void printProximityReadings();

void printDipSwitchReading();

void calibrateValue();

void setup()
{
    bluetooth::setup();
    dipSwitch::setup();
    fsm::setup();

    // push button for start routine

    menu.addOption("FSM", fsmSetup, fsmAction, fsmCleanup);
    menu.addOption(
        "Elegir metal", []()
        { fsm::configValues = &fsm::metalRing;Terminal.println("Metal elegido!"); },
        nullptr, nullptr);
    menu.addOption("Sensores de linea", printReadingsSetup, printLineReadings, nullptr);
    menu.addOption("Sensores de proximidad", printReadingsSetup, printProximityReadings, nullptr);
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
    menu.addOption("Calibrar parámetro", calibrateValue, nullptr, nullptr);
    calibrationMenu.addField("step time [ms]", &motors::STEP_DURATION_MS);

    calibrationMenu.addField("Norm srch speed [1-14]", &fsm::configValues->normalSearchSpeed);
    // calibrationMenu.addField("Norm srch init speed [1-6]", &fsm::configValues->normalInitialSearchSpeed);
    // calibrationMenu.addField("Norm srch init dur [ms]", &fsm::configValues->normalInitialSearchDuration);

    /* Avoid fall */
    // calibrationMenu.addField("av fall: rev dur [ms]", &fsm::configValues->avoidFallFrontReverseDuration);
    // calibrationMenu.addField("av fall: rev speed [1-14]", &fsm::configValues->avoidFallFrontReverseSpeed);
    // calibrationMenu.addField("av fall: turn dur [ms]", &fsm::configValues->avoidFallFrontMaxTurnDuration);
    // calibrationMenu.addField("av fall: turn speed [1-14]", &fsm::configValues->avoidFallFrontTurnSpeed);

    /* Aim front side */
    // calibrationMenu.addField("aim fs: trn spd in [1-14]", &fsm::configValues->aimFrontSideSpeedInner);
    // calibrationMenu.addField("aim fs: trn spd out [1-14]", &fsm::configValues->aimFrontSideSpeedOuter);
    // calibrationMenu.addField("aim fs: trn dur  [ms]", &fsm::configValues->aimFrontSideMaxTurnDuration);

    /* Aim side */
    calibrationMenu.addField("aim s: trn spd  [1-14]", &fsm::configValues->aimSideSpeedOuter);
    calibrationMenu.addField("aim s: trn dur  [ms]", &fsm::configValues->aimSideMaxTurnDuration);

    /* Attack front */
    // calibrationMenu.addField("AF: full gas speed [1-6]", &attackFront_fsm::fullGasSpeed);
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
    // calibrationMenu.addField("WS: forward speed [1-6]", &fsm::configValues->waitSensorsMoveForwardSpeed);
    // calibrationMenu.addField("WS: forward duration [ms]", &fsm::configValues->waitSensorsMoveForwardDuration);
    // calibrationMenu.addField("WS: wait duration [ms]", &fsm::configValues->waitSensorsWaitMaxDuration);

    /* Avoid back */
    // calibrationMenu.addField("av bck: trn spd [1-6]", &fsm::configValues->avoidBackTurnSpeed);
    // calibrationMenu.addField("av bck: trn drtn [ms]", &fsm::configValues->avoidBackMaxTurnDuration);

    /* Avoid back in J*/
    // calibrationMenu.addField("av bck J: trn spd innr [1-6]", &fsm::configValues->avoidBackInJInnerSpeed);
    // calibrationMenu.addField("av bck J: trn spd outr [1-6]", &fsm::configValues->avoidBackInJOuterSpeed);
    // calibrationMenu.addField("av bck J: trn drtn [ms]", &fsm::configValues->avoidBackInJMaxTurnDuration);

    RGBLed::showGreen();
}

void loop()
{
    menu.run();
}

void fsmSetup()
{
    pinMode(KILL_SWITCH_START, INPUT_PULLDOWN);
    RGBLed::showYellow();
    while (!digitalRead(KILL_SWITCH_START))
    {
    }
    int initialStrategy = dipSwitch::readInt();
    fsm::initialAction(initialStrategy);
    RGBLed::showYellow();
    delay(1000);
    RGBLed::turnOff();
    delay(1000);
    RGBLed::showYellow();
    delay(1000);
    RGBLed::turnOff();
    delay(1000);
    RGBLed::showRed();
    delay(1000);
}

void fsmAction()
{
    if (digitalRead(KILL_SWITCH_START))
    {
        fsm::state();
    }
    else
    {
        fsm::cleanupAction();
        RGBLed::showGreen();
        while (true)
        {
        }
    }
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

void calibrateValue()
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
#endif