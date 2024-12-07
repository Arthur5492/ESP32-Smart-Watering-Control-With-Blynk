#include "soilMoisture.h"

SoilMoisture soilMoisture;


void SoilMoisture::setPIN(uint8_t pin) 
{ 
  _inputPin = pin; 
  pinMode(_inputPin, INPUT);
};

void SoilMoisture::setPowerPIN(uint8_t pin)
{
  _powerPin = pin;
}

int SoilMoisture::read()
{
  // digitalWrite(_powerPin,HIGH); //?Better for real world logic
  _value = analogRead(_inputPin);
  // digitalWrite(_powerPin,LOW);

  _percentValue = map(_value,0,4095,100,0);

  return _percentValue;
}