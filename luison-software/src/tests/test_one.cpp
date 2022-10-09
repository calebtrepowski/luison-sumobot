#ifdef TEST_ONE
#include <Arduino.h>
#include "onOffControl.h"
#include "motor.h"
#include "dipSwitch.h"
#include "line.h"

#ifdef DISABLE_WIFI
#include <WiFi.h>
#include <esp_wifi.h>
#include "driver/adc.h"

void disableWiFi()
{
  WiFi.mode(WIFI_OFF);
}
#endif

void printValues()
{
  Serial.print(line::frontLeft.value);
  Serial.print("\t");
  Serial.println(line::frontRight.value);
  Serial.print(line::backLeft.value);
  Serial.print("\t");
  Serial.print(line::backRight.value);
  Serial.println();
  delay(100);
}

volatile bool state;

unsigned long buttonTime = 0;
unsigned long lastButtonTime = 0;
unsigned long lastOnTime = 0;

const uint_fast8_t debounceTime = 10;   // ms
const uint_fast8_t minimumOnTime = 500; // ms

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
      }
      state = !state;
      lastOnTime = buttonTime;
    }
  }
  lastButtonTime = buttonTime;
}

void setup()
{
#ifdef DISABLE_WIFI
  disableWiFi();
#endif

  motors::setup();
  onOffControl::setup();
  line::setup();
  dipSwitch::setup();
  strategy = dipSwitch::readInt();
  attachInterrupt(onOffControl::control.pin, toggleStateISR, RISING);
  state = false;
  // Serial.begin(9600);
}

void loop()
{
  // Serial.println(state);
  line::readValues();
  if (state)
  {
    // Serial.println(1);
    switch (strategy)
    {
    case 1:
      printValues();
      if (LINE_FRONT_DETECTED)
      {
        motors::brake();
        motors::setSpeedBoth(0U);
      }
      else
      {
        motors::setSpeedBoth(5U);
        motors::goForward();
      }
      break;
    case 2:
      motors::setSpeedBoth(1U);
      motors::goBack();
      break;
    default:
      motors::brake();
      motors::setSpeedBoth(0U);
      break;
    }
  }
  else
  {
    // Serial.println(0);
    motors::brake();
    motors::setSpeedBoth(0U);
  }
}
#endif