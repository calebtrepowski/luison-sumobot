// #include <Arduino.h>
// #include "menu/menuDabbleTerminal.hpp"
// #include "bluetooth.h"
// #include "proximity.h"
// #include "line.h"
// #ifdef ENABLE_GYRO
// #include "gyroscope.h"
// #endif
// #include "motorDriver.h"
// #include "fsm/fsm.h"

// void fsmSetup();
// void fsmAction();
// void fsmCleanup();

// unsigned long referenceTime;
// void printLineReadingsSetup();
// void printLineReadings();

// MenuDabbleTerminal menu;

// void setup()
// {
//     Dabble.begin("LuisonBT");

//     fsm::setup();

//     menu.addOption("FSM", fsmSetup, fsmAction, fsmCleanup);
//     menu.addOption("Sensores de linea", printLineReadingsSetup, printLineReadings, nullptr);
// }

// void loop()
// {
//     menu.run();
// }

// void fsmSetup()
// {
//     fsm::priorState = NULL;
//     fsm::state = fsm::idle;
//     fsm::state();
//     fsm::state = fsm::normalSearch;
// }

// void fsmAction()
// {
//     fsm::state();
// }

// void fsmCleanup()
// {
//     fsm::priorState = NULL;
//     fsm::state = fsm::idle;
//     fsm::state();
// }
// void printLineReadingsSetup()
// {
//     referenceTime = millis();
// }

// void printLineReadings()
// {
//     if (millis() % referenceTime > 500)
//     {
//         line::readValues();
//         Terminal.println(line::valuesToString());
//     }
// }