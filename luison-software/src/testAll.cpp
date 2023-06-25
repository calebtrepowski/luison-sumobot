#ifdef TEST_ALL
#include <Arduino.h>
#include "menu/menuDabbleTerminal.hpp"
#include "menu/calibrationMenu.hpp"

#include "bluetooth.h"

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

void setup()
{
    bluetooth::setup();
    fsm::setup();

    menu.addOption("FSM", fsmSetup, fsmAction, fsmCleanup);
    menu.addOption("Sensores de linea", printReadingsSetup, printLineReadings, nullptr);
    menu.addOption("Sensores de proximidad", printReadingsSetup, printProximityReadings, nullptr);
    menu.addOption(
        "Motores: adelante", []()
        { motors::goForward(NORMAL_SEARCH_SPEED); },
        []() {}, motors::brake);
    menu.addOption(
        "Motores: atras", []()
        { motors::goBack(3); },
        []() {}, motors::brake);
    menu.addOption(
        "Motores: izquierda", []()
        { motors::turnLeft(3); },
        []() {}, motors::brake);
    menu.addOption(
        "Motores: derecha", []()
        { motors::turnRight(3); },
        []() {}, motors::brake);
    menu.addOption("Calibrar parámetro", calibrateValue, nullptr, nullptr);

    calibrationMenu.addField("Normal search speed [1-6]", &NORMAL_SEARCH_SPEED);
}

void loop()
{
    menu.run();
}

void fsmSetup()
{
    fsm::priorState = NULL;
    fsm::state = fsm::idle;
    fsm::state();
    fsm::state = fsm::normalSearch;
}

void fsmAction()
{
    fsm::state();
}

void fsmCleanup()
{
    fsm::priorState = NULL;
    fsm::state = fsm::idle;
    fsm::state();
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