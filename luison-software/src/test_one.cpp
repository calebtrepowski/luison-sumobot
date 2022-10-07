#ifdef TEST_ONE
#include <Arduino.h>
#include "onOffControl.h"
#include "motor.h"
#include "dipSwitch.h"

#ifdef DISABLE_WIFI
#include <WiFi.h>
#include <esp_wifi.h>
#include "driver/adc.h"

void disableWiFi()
{
  WiFi.mode(WIFI_OFF);
}
#endif

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
  dipSwitch::setup();
  strategy = dipSwitch::readInt();
  attachInterrupt(onOffControl::control.pin, toggleStateISR, RISING);
  state = false;
  Serial.begin(115200);
}

void loop()
{
  if (state)
  {
    // Serial.println(1);
    switch (strategy)
    {
    case 1:
      motors::setSpeedBoth(1U);
      motors::goForward();
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