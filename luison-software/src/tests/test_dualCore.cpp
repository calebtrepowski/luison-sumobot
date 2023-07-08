#ifdef TEST_DUAL_CORE
#include <Arduino.h>
#include <sstream>
#include "esp_task_wdt.h"
#include "esp_err.h"

#include "bluetooth.h"
#include "line.h"
#include "proximity.h"
#include "gyroscope.h"
#include "motorDriver.h"
#include "fsm/fsm.h"

TaskHandle_t bluetoothTaskHandle;
TaskHandle_t actionTaskHandle;

void bluetoothMenuTask(void *pvParameters);
void emptyTask(void *pvParameters) {}
void testLineSensorsTask(void *pvParameters);
void testProximitySensorsTask(void *pvParameters);
void FSMTask(void *pvParameters);
const char *getMenuToString();

BaseType_t CORE_0 = 0;
BaseType_t CORE_1 = 1;

void setup()
{
    Serial.begin(MONITOR_SPEED);

    bluetooth::setup();
    proximity::setup();
    line::setup();
    gyroscope::setup();
    motors::setup();

    fsm::priorState = NULL;
    fsm::state = fsm::idle;

    xTaskCreatePinnedToCore(bluetoothMenuTask, "Bluetooth_Menu", 8000, NULL, 1, &bluetoothTaskHandle, CORE_1);
    vTaskDelete(NULL);
}

void loop()
{
}

void bluetoothMenuTask(void *pvParameters)
{
    String command;
    int choice;
    bool taskRunning = false;

    while (true)
    {
        Dabble.processInput();
        if (Terminal.available() > 0)
        {
            command = Terminal.readString();
            choice = command.toInt();
            command = "";

            switch (choice)
            {
            case 0:
                motors::brake();
                Terminal.println(getMenuToString());
                vTaskDelete(actionTaskHandle);
                break;
            case 2:
            {
                BaseType_t taskCreationSuccess = xTaskCreatePinnedToCore(testLineSensorsTask, "TestLineSensorsTask", 8000, NULL, 1, &actionTaskHandle, CORE_0);
                if (taskCreationSuccess == pdFAIL)
                {
                    Terminal.println("Error al crear la tarea");
                }
                break;
            }
            default:
                motors::brake();
                Terminal.println("Comando no válido.");
                Terminal.println(getMenuToString());
                break;
            }
        }
    }
}

void testLineSensorsTask(void *pvParameters)
{
    Terminal.println("Enviar 0 para detener.");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
    while (true)
    {
        line::readValues();
        Terminal.println(line::valuesToString());
        vTaskDelayUntil(&xLastWakeTime, xDelay500ms);
    }
}

void testProximitySensorsTask(void *pvParameters)
{
    Terminal.println("Enviar 0 para detener.");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
    while (true)
    {
        line::readValues();
        Terminal.println(line::valuesToString());
        vTaskDelayUntil(&xLastWakeTime, xDelay500ms);
    }
}

void FSMTask(void *pvParameters)
{
    Terminal.println("Enviar 0 para detener.");
    fsm::state = fsm::normalSearch;

    while (true)
    {
        Terminal.println("antes de state");
        fsm::state();
        Terminal.println("despues de state");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

const char *getMenuToString()
{
    std::ostringstream menuText;
    menuText << "=== Probar: ===" << '\n';
    menuText << "1. Sensores de proximidad" << '\n';
    menuText << "2. Sensores de linea" << '\n';
    menuText << "3. MPU" << '\n';
    menuText << "4. Motores (adelante)" << '\n';
    menuText << "5. Motores (reversa)" << '\n';
    menuText << "6. FSM" << '\n';
    menuText << "7. minimum" << '\n';
    return menuText.str().data();
}

#endif