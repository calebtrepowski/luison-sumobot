#ifdef TEST_ALL
#include <Arduino.h>
#include "menu/menuDabbleTerminal.hpp"

#include "bluetooth.h"

/* fsm already includes line, proximity, motor and gyro */
#include "fsm/fsm.h"

MenuDabbleTerminal menu;

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
        { motors::goForward(3); },
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
#endif