#ifndef _debug_utils_h_
#define _debug_utils_h_

#include <Arduino.h>

#ifdef DEBUG_SERIAL
#define DEBUG_BEGIN(...)     \
  Serial.begin(__VA_ARGS__); \
  printSystemInfo();
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#elif defined(DEBUG_BLUETOOTH)
#define DEBUG_BEGIN(...) Serial.begin(__VA_ARGS__)
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_BEGIN(...)
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

#if defined(DEBUG_SERIAL) || defined(DEBUG_BLUETOOTH)
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