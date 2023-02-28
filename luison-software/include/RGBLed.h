#ifndef _led_rgb_h_
#define _led_rgb_h_

#include <Arduino.h>
#include <esp32-hal-rgb-led.h>
#include "pinNumbers.h"

namespace RGBLed
{
    const uint_fast8_t BRIGHTNESS_PERCENTAGE = 10; // 0 % - 100 %
    const uint_fast8_t BRIGHTNESS_VALUE = (uint8_t)(255/100) * BRIGHTNESS_PERCENTAGE;

    void showRed()
    {
        neopixelWrite(RGB_LED_PIN, BRIGHTNESS_VALUE, 0, 0);
    }

    void showGreen()
    {
        neopixelWrite(RGB_LED_PIN, 0, BRIGHTNESS_VALUE, 0);
    }

    void showBlue()
    {
        neopixelWrite(RGB_LED_PIN, 0, 0, BRIGHTNESS_VALUE);
    }

}

#endif