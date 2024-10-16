#ifndef WATERLEVEL_H
#define WATERLEVEL_H

#include <Arduino.h>

namespace waterLevel
{
  uint8_t pin_topLevel;
  uint8_t pin_bottomLevel;
  void setup(uint8_t PIN1,uint8_t PIN2)
  {
    pin_topLevel =    PIN1;
    pin_bottomLevel = PIN2;

    pinMode(pin_topLevel, INPUT);
    pinMode(pin_bottomLevel, INPUT);
  }

  /// @brief  Retorna true se o sensor inferior estiver false
  bool isLow()
  {
    return digitalRead(pin_bottomLevel) == LOW;
  }


  /// @brief Retorna true se  o sensor superior estiver cheio
  bool isFull()
  {
    return digitalRead(pin_topLevel) == HIGH; 
  }

}




#endif
