#ifndef _blueto_h
#define _blueto_h
#include <Arduino.h>

#include <BluetoothSerial.h>
#include "fsm/fsm.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

namespace bluetooth
{
    BluetoothSerial SerialBT;

    void setup()
    {
        SerialBT.begin("virus"); // Bluetooth device name
        SerialBT.println("Iniciado!");
    }

    void echo()
    {
        if (SerialBT.available())
        {
            SerialBT.write(SerialBT.read());
        }
    }

    bool loadStart(uint_fast8_t &active)
    {
        if (SerialBT.available())
        {
            uint_fast8_t tmp = SerialBT.read();
            if (tmp == '1')
            {
                SerialBT.println("Iniciado!");
                active = 1;
                return true;
            }
            else if (tmp == '0')
            {
                SerialBT.println("Detenido!");
                active = 0;
            }
            SerialBT.flush();
        }
        return false;
    }
}

#endif