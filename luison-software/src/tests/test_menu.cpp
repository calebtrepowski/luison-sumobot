#include <Arduino.h>

#include "menu/menuDabbleTerminal.hpp"

void action1();
void action2();
void action2cleanup();
void action3();

MenuDabbleTerminal menu;

void setup()
{
    Dabble.begin("LuisonBT");

    menu.addOption("Option 1", action1, nullptr, nullptr);
    menu.addOption("Option 2", nullptr, action2, action2cleanup);
    menu.addOption("Option 3", action3, nullptr, nullptr);
}

void loop()
{
    menu.run();
}

void action1()
{
    Terminal.println("Option 1 selected");
}

void action2()
{
    Terminal.println("Option 2 selected");
    delay(500);
}
void action2cleanup()
{
    Terminal.println("Terminado opcion 2");
}

void action3()
{
    Terminal.println("Option 3 selected");
}