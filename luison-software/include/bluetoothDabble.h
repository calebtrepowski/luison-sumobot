#ifndef _bluetooth_dabble_h_
#define _bluetooth_dabble_h_

#if DEBUG_METHOD == 4 || ON_OFF_METHOD == 4

#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>

namespace bluetooth
{
    void setup()
    {
        Dabble.begin("JBL Flip 4");
    }

    void echo()
    {
        Dabble.processInput();
        if (Terminal.available() != 0)
        {
            Terminal.println(Terminal.readString());
        }
    }

    bool loadStart(uint_fast8_t &active)
    {
        Dabble.processInput();
        if (Terminal.available() != 0)
        {
            String terminalValue = Terminal.readString();
            int choice = terminalValue.toInt();
            
            if (choice == 1)
            {
                Terminal.println("Iniciado!");
                active = 1;
                return true;
            }
            else if (choice == 0)
            {
                Terminal.println("Detenido!");
                active = 0;
            }
            else
            {
                Terminal.println(terminalValue);
            }
        }

        return false;
    }
}
#endif

#endif