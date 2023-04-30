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

    uint8_t txValue = 0;
    std::string rxValue;
    bool bufferedRxData = false;

    class MyServerCallbacks : public BLEServerCallbacks
    {
        void onConnect(BLEServer *pServer)
        {
            deviceConnected = true;
        };

        void onDisconnect(BLEServer *pServer)
        {
            deviceConnected = false;
        }
    };

    class MyCallbacks : public BLECharacteristicCallbacks
    {
        void onWrite(BLECharacteristic *pCharacteristic)
        {
            rxValue = pCharacteristic->getValue();
            bufferedRxData = true;
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
            if (bufferedRxData)
            {
                pCharacteristic->setValue(rxValue.data());
                pCharacteristic->notify();
                bufferedRxData = false;
            }
        }
    }

    bool loadStart(uint_fast8_t &active)
    {
        if (rxValue.length() > 0)
        {
            if (rxValue.front() == '1')
            {
                pCharacteristic->setValue("Iniciado!");
                pCharacteristic->notify();
                active = 1;
                return true;
            }
            else if (rxValue.front() == '0')
            {
                pCharacteristic->setValue("Detenido!");
                pCharacteristic->notify();
                active = 0;
            }
            else
            {
                pCharacteristic->setValue(rxValue);
                pCharacteristic->notify();
            }
            rxValue.clear();
        }
        return false;
    }

    void sendData(std::string value)
    {
        pCharacteristic->setValue(value.data());
        pCharacteristic->notify();
    }

    void sendData(float &value)
    {
        pCharacteristic->setValue(value);
        pCharacteristic->notify();
    }
}

#endif

#endif