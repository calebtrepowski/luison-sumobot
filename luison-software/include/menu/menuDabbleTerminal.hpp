#ifndef _menu_dabble_terminal_hpp_
#define _menu_dabble_terminal_hpp_

#include "menu.hpp"
#include <DabbleESP32.h>

class MenuDabbleTerminal : public Menu
{
public:
    MenuDabbleTerminal() : Menu() {}
    ~MenuDabbleTerminal() {}

    void displayMenu()
    {
        Terminal.print(menuText.data());
    }

    void showMessage(const char *message)
    {
        Terminal.print(message);
    }

    bool inputAvailable()
    {
        Dabble.processInput();
        return Terminal.available() > 0;
    }

    int readInput()
    {
        return Terminal.readString().toInt();
    }
};

#endif