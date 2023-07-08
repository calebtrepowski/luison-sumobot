#ifdef BENCHMARK
#include <Arduino.h>
#include <esp_timer.h>
#include <sstream>
#include "debugUtils.h"

#include "proximity.h"

void measureFunction(const uint64_t measurements);

void setup()
{
  /* initialize requirements here: */

  DEBUG_BEGIN(MONITOR_SPEED);
  delay(3000);
}

void loop()
{
  measureFunction(50000ULL);
  while (true)
  {
  }
}

void measureFunction(const uint64_t MEASUREMENTS)
{
  DEBUG_PRINTLN("Starting measurement...");

  uint64_t start = esp_timer_get_time();

  for (int retries = 0; retries < MEASUREMENTS; ++retries)
  {
    /* invoke here the function to benchmark */
    Dabble.processInput();
  }

  uint64_t end = esp_timer_get_time();

  std::ostringstream aux;
  aux << MEASUREMENTS << " iterations took " << (end - start)
      << " microseconds (" << (double)(end - start) / MEASUREMENTS
      << ") microseconds per invocation)\n";
  DEBUG_PRINTLN(aux.str().data());
}

#endif