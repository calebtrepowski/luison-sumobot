#ifdef BENCHMARK
#include <Arduino.h>
#include <esp_timer.h>
#include "debugUtils.h"

#include "proximity.h"

void measureFunction(const uint64_t measurements);

void setup()
{
  /* initialize requirements here: */

  DEBUG_BEGIN(MONITOR_SPEED);
}

void loop()
{
  measureFunction(5000000ULL);
  while(true){

  }
}

void measureFunction(const uint64_t MEASUREMENTS)
{
  DEBUG_PRINTLN("Starting measurement...");

  uint64_t start = esp_timer_get_time();

  for (int retries = 0; retries < MEASUREMENTS; ++retries)
  {
    /* invoke here the function to benchmark */
    
  }

  uint64_t end = esp_timer_get_time();

  DEBUG_PRINT(MEASUREMENTS);
  DEBUG_PRINT(" iterations took ");
  DEBUG_PRINT((end - start));
  DEBUG_PRINT(" microseconds (");
  DEBUG_PRINT((double)(end - start) / MEASUREMENTS);
  DEBUG_PRINTLN(") microseconds per invocation)");
}

#endif