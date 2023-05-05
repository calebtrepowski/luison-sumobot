#ifndef _debug_utils_h_
#define _debug_utils_h_

#include <Arduino.h>

#if DEBUG_METHOD == 1
#define DEBUG_BEGIN(...)     \
  Serial.begin(__VA_ARGS__); \
  printSystemInfo();
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#elif DEBUG_METHOD == 2
#include "bluetoothSerial.h"
using namespace bluetooth;
#define DEBUG_BEGIN(...) SerialBT.begin(__VA_ARGS__)
#define DEBUG_PRINT(...) SerialBT.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) SerialBT.println(__VA_ARGS__)
#elif DEBUG_METHOD == 3
#include "bluetoothBLE.h"
using namespace bluetooth;
#define DEBUG_BEGIN(...)
#define DEBUG_PRINT(...) BLEPrint(__VA_ARGS__)
#define DEBUG_PRINTLN(...) BLEPrintln(__VA_ARGS__)
#else
#define DEBUG_BEGIN(...)
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

#if DEBUG_METHOD != 0
#include <esp_timer.h>

template <typename R>
void benchmarkFunction(R (*function)(void), const uint64_t MEASUREMENTS)
{

  DEBUG_PRINTLN("Starting measurement...");
  uint64_t start = esp_timer_get_time();
  for (int retries = 0; retries < MEASUREMENTS; ++retries)
  {
    function();
  }

  uint64_t end = esp_timer_get_time();

  DEBUG_PRINT(MEASUREMENTS);
  DEBUG_PRINT(" iterations took ");
  DEBUG_PRINT((end - start));
  DEBUG_PRINT(" microseconds (");
  DEBUG_PRINT((double)(end - start) / MEASUREMENTS);
  DEBUG_PRINTLN(") microseconds per invocation)");
}

#include <soc/rtc.h>

void printSystemInfo(void)
{
  rtc_cpu_freq_config_t config = {};
  rtc_clk_cpu_freq_get_config(&config);
  DEBUG_PRINTLN("\n\n======================");
  DEBUG_PRINT("CPU Clock is ");
  DEBUG_PRINT(config.freq_mhz);
  DEBUG_PRINTLN(" MHz");
  DEBUG_PRINTLN("======================");
}
#else

template <typename R>
void benchmarkFunction(R (*function)(void), const uint64_t MEASUREMENTS)
{
}

void printSystemInfo(void)
{
}

#endif

#endif