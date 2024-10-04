#ifndef WATERLEVEL_H
#define WATERLEVEL_H

#include <Arduino.h>

namespace waterLevel
{
  size_t PIN = 13;
  void setup()
  {
    pinMode(PIN, INPUT);
  }

  bool isHIGH()
  {
    return digitalRead(PIN) == HIGH;
  }
  
}




#endif
