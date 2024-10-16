#ifndef SOLENOIDE_H
#define SOLENOIDE_H

#include <Arduino.h>

namespace solenoide
{
  uint8_t _pin;
  bool actualState;

  void setPin(uint8_t PIN)
  {
    _pin = PIN;
    pinMode(_pin,OUTPUT);
  };
  

  void turnOn()
  {
    digitalWrite(_pin,HIGH);
    actualState = HIGH;
    Serial.print("Solenoide ativada \n");
  }

  void turnOff()
  {
    digitalWrite(_pin,LOW);
    actualState = LOW;
    Serial.print("Solenoide Desativada \n");
  }
}

#endif