#ifndef _bluetooth_serial_h_
#define _bluetooth_serial_h_

#if defined(DEBUG_BLUETOOTH_SERIAL)

#include "bluetooth.h"

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

namespace bluetooth
{
    BluetoothSerial SerialBT;

    void setup()
    {
        SerialBT.begin("LUISON_BT");
        SerialBT.println("Bluetooth iniciado!");
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
            uint_fast8_t receivedValue = SerialBT.read();
            if (receivedValue == '1')
            {
                SerialBT.println("Iniciado!");
                active = 1;
                return true;
            }
            else if (receivedValue == '0')
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

#endif