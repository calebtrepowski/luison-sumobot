#ifndef _debug_utils_h_
#define _debug_utils_h_

#ifdef DEBUG_SERIAL
  #define DEBUG_BEGIN(...) Serial.begin(__VA_ARGS__)
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

#endif