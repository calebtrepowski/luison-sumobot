#ifndef _bluetooth_ble_h_
#define _bluetooth_ble_h_

#if defined(DEBUG_BLUETOOTH_BLE)
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

namespace bluetooth
{
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

    BLECharacteristic *pCharacteristic;

    bool deviceConnected = false;

    std::string rxValue;

    class MyServerCallbacks : public BLEServerCallbacks
    {
        void onConnect(BLEServer *pServer)
        {
            deviceConnected = true;
        };

        void onDisconnect(BLEServer *pServer)
        {
            deviceConnected = false;
            pServer->getAdvertising()->start();
        }
    };

    class MyCallbacks : public BLECharacteristicCallbacks
    {
        void onWrite(BLECharacteristic *pCharacteristic)
        {
            rxValue = pCharacteristic->getValue();
        }
    };

    void setup()
    {
        BLEDevice::init("LUISON_BT");

        // Create the BLE Server
        BLEServer *pServer = BLEDevice::createServer();
        pServer->setCallbacks(new MyServerCallbacks());

        // Create the BLE Service
        BLEService *pService = pServer->createService(SERVICE_UUID);

        // Create a BLE Characteristic
        pCharacteristic = pService->createCharacteristic(
            CHARACTERISTIC_UUID_TX,
            BLECharacteristic::PROPERTY_NOTIFY);

        pCharacteristic->addDescriptor(new BLE2902());

        BLECharacteristic *pCharacteristic = pService->createCharacteristic(
            CHARACTERISTIC_UUID_RX,
            BLECharacteristic::PROPERTY_WRITE);

        pCharacteristic->setCallbacks(new MyCallbacks());

        // Start the service
        pService->start();

        // Start advertising
        pServer->getAdvertising()->start();
    }

    void echo()
    {
        if (deviceConnected)
        {
            if (rxValue.length() > 0)
            {
                pCharacteristic->setValue(rxValue.data());
                pCharacteristic->notify();
                rxValue.clear();
            }
        }
    }

    void BLEPrint(std::string value);
    void BLEPrint(uint32_t value);
    void BLEPrint(uint64_t value);
    void BLEPrint(float value);
    void BLEPrint(double value);
    void BLEPrintln(std::string value);
    void BLEPrintln(uint32_t value);
    void BLEPrintln(uint64_t value);
    void BLEPrintln(float value);
    void BLEPrintln(double value);

    /**
     * For some reason, for rxValue = "1" it keeps entering
     * the corresponding if block. In order to get it work,
     * in the BLE client, send "1" and inmediately after "" (blank)
     */
    bool loadStart(uint_fast8_t &active)
    {
        if (deviceConnected)
        {

            if (rxValue.length() > 0)
            {
                if (rxValue.front() == '1')
                {
                    BLEPrintln(std::string("Iniciado!"));
                    active = 1;
                    return true;
                }
                else if (rxValue.front() == '0')
                {
                    BLEPrintln(std::string("Detenido!"));
                    active = 0;
                }
                else
                {
                    BLEPrintln(rxValue);
                }
                rxValue.clear();
            }
        }
        return false;
    }

    void BLEPrint(std::string value)
    {
        pCharacteristic->setValue(value.data());
        pCharacteristic->notify();
    }

    void BLEPrint(uint32_t value)
    {
        pCharacteristic->setValue(&(uint8_t &)value, sizeof(value));
        pCharacteristic->notify();
    }

    void BLEPrint(uint64_t value)
    {
        pCharacteristic->setValue(&(uint8_t &)value, sizeof(value));
        pCharacteristic->notify();
    }

    void BLEPrint(float value)
    {
        pCharacteristic->setValue(value);
        pCharacteristic->notify();
    }

    void BLEPrint(double value)
    {
        pCharacteristic->setValue(value);
        pCharacteristic->notify();
    }

    void BLEPrintln(std::string value)
    {
        pCharacteristic->setValue(value.append("\n").data());
        pCharacteristic->notify();
    }

    void BLEPrintln(uint32_t value)
    {
        pCharacteristic->setValue(&(uint8_t &)value, sizeof(value));
        pCharacteristic->setValue(pCharacteristic->getValue().append("\n").data());
        pCharacteristic->notify();
    }

    void BLEPrintln(uint64_t value)
    {
        pCharacteristic->setValue(&(uint8_t &)value, sizeof(value));
        pCharacteristic->setValue(pCharacteristic->getValue().append("\n").data());
        pCharacteristic->notify();
    }

    void BLEPrintln(float value)
    {
        pCharacteristic->setValue(&(uint8_t &)value, sizeof(value));
        pCharacteristic->setValue(pCharacteristic->getValue().append("\n").data());
        pCharacteristic->notify();
    }

    void BLEPrintln(double value)
    {
        pCharacteristic->setValue(&(uint8_t &)value, sizeof(value));
        pCharacteristic->setValue(pCharacteristic->getValue().append("\n").data());
        pCharacteristic->notify();
    }
}

#endif

#endif