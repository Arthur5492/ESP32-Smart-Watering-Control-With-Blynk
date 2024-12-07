/**
 * @file soilMoisture.h
 * @brief Provides functionality to monitor and manage soil moisture levels.
 * @details This header defines the SoilMoisture class, which allows configuration of input and power pins,
 *          reading analog values from the sensor, and converting them into a percentage for better usability.
 * @see https://github.com/Arthur5492
 */

#ifndef SOILMOSTURE_H
#define SOILMOSTURE_H

#pragma once

#include <Arduino.h>

class SoilMoisture
{
  public:
  SoilMoisture() = default;
  ~SoilMoisture(){};

  /// @param pin SoilMoisture Input PIN
  void setPIN(uint8_t pin);

  /// @param pin SoilMoisture VCC PIN() 
  void setPowerPIN(uint8_t pin);

  int read();

  int getPercentValue() { return _percentValue; };

  private:
    uint8_t _inputPin;
    uint8_t _powerPin;
    int _value = 0;
    int _percentValue = 0;
};

extern SoilMoisture soilMoisture;




#endif