#ifdef TEST_DUAL_CORE
#include <Arduino.h>
#include "proximity.h"
#include "dipSwitch.h"
#include "motor.h"
#include "onOffControl.h"
#include "line.h"
// #define INCLUDE_xTaskResumeFromISR

TaskHandle_t taskRead;
TaskHandle_t taskExecute;
TaskHandle_t taskPrintDot;
TaskHandle_t taskPrintDash;

void printDot(void *pvParameters);
void printDash(void *pvParameters);
void readSensors(void *pvParameters);
void printSensors(void *pvParameters);
void execute(void *pvParameters);

volatile bool state;

unsigned long buttonTime = 0;
unsigned long lastButtonTime = 0;
unsigned long lastOnTime = 0;

const uint_fast8_t debounceTime = 10;    // ms
const uint_fast8_t minimumOnTime = 2000; // ms

uint_fast8_t strategy = 0;

void IRAM_ATTR toggleStateISR()
{
    buttonTime = millis();
    if (buttonTime - lastButtonTime > debounceTime)
    {
        if (buttonTime - lastOnTime > minimumOnTime)
        {
            // para que no se apague si el árbitro mantiene apretado
            // hacer lo que se requiera, idealmente interrumpir/empezar un task
            if (!state)
            {
                strategy = dipSwitch::readInt();
                vTaskResume(taskExecute);
            }
            else
            {
                motors::brake();
                motors::setSpeedBoth(0U);
                vTaskSuspend(taskExecute);
            }
            state = !state;
            lastOnTime = buttonTime;
        }
    }
    lastButtonTime = buttonTime;
}

void setup()
{
    // pinMode(13, INPUT_PULLDOWN);
    motors::setup();
    onOffControl::setup();
    proximity::setup();
    line::setup();
    dipSwitch::setup();
    strategy = dipSwitch::readInt();
    // line::setup();
    // Serial.begin(9600);

    xTaskCreatePinnedToCore(readSensors, "READ_SENSORS", 2048, NULL, 1, &taskPrintDot, 1);
    // xTaskCreatePinnedToCore(printSensors, "PRINT_SENSORS", 2048, NULL, 1, &taskPrintDot, 0);
    xTaskCreatePinnedToCore(execute, "EXECUTE", 2048, NULL, 1, &taskExecute, 0);
    // vTaskSuspend(taskExecute);
    // xTaskCreate(printDot, "PRINT_DOT", 2048, NULL, 1, &taskPrintDot);
    // xTaskCreate(printDash, "PRINT_DOT", 2048, NULL, 1, &taskPrintDash);
}

void loop()
{
    // vTaskSuspend(taskPrintDot);
    // vTaskResume(taskPrintDash);
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    // vTaskSuspend(taskPrintDash);
    // vTaskResume(taskPrintDot);
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void printDot(void *pvParameters)
{
    for (;;)
    {
        Serial.println(".");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void printDash(void *pvParameters)
{
    for (;;)
    {
        Serial.println("-");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void readSensors(void *pvParameters)
{
    for (;;)
    {
        line::readValues();
        proximity::readStates();
    }
}
void printSensors(void *pvParameters)
{
    // for (;;)
    // {
    //     Serial.print(proximity::frontLeft.state);
    //     Serial.print(" ");
    //     Serial.print(proximity::frontCenter.state);
    //     Serial.print(" ");
    //     Serial.println(proximity::frontRight.state);

    //     Serial.print(proximity::left.state);
    //     Serial.print("   ");
    //     Serial.println(proximity::right.state);

    //     Serial.print("  ");
    //     Serial.println(proximity::back.state);
    //     vTaskDelay(200 / portTICK_PERIOD_MS);
    // }
    for (;;)
    {
        Serial.print(line::frontLeft.value);
        Serial.print("\t");
        Serial.println(line::frontRight.value);
        Serial.print(line::backLeft.value);
        Serial.print("\t");
        Serial.println(line::backRight.value);
        Serial.println();
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

// #define LINE_FRONT_LEFT_DETECTED
void execute(void *pvParameters)
{
    // if (state)
    // {
    // Serial.println(1);
    if (line::frontLeft.value < line::frontLeft.referenceValue || line::frontRight.value < line::frontRight.referenceValue)
    {
        motors::brake();
        motors::setSpeedBoth(0U);
    }
    else
    {
        motors::setSpeedBoth(1U);
        motors::goForward();
    }
    // switch (strategy)
    // {
    // case 1:
    //     if (line::frontLeft.value < line::frontLeft.referenceValue || line::frontRight.value < line::frontRight.referenceValue)
    //     {
    //         motors::brake();
    //         motors::setSpeedBoth(0U);
    //     }
    //     else
    //     {
    //         motors::setSpeedBoth(1U);
    //         motors::goForward();
    //     }
    //     break;
    // case 2:
    //     if (line::frontLeft.value < line::frontLeft.referenceValue || line::frontRight.value < line::frontRight.referenceValue)
    //     {
    //         motors::brake();
    //         motors::setSpeedBoth(0U);
    //     }
    //     else
    //     {
    //         motors::setSpeedBoth(1U);
    //         motors::goBack();
    //     }
    //     break;
    // default:
    //     motors::brake();
    //     motors::setSpeedBoth(0U);
    //     break;
    // }
    // }
    // else
    // {
    //     // Serial.println(0);
    // }
}

#endif