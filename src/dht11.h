/**
 * @file dht11.h
 * @brief Handles initialization and data retrieval from a DHT11 sensor.
 * @details The DHT object is created dynamically to allow reconfiguration of the sensor pin using the `setPIN` method,
 *          overcoming the limitation of pin assignment being fixed at construction.
 * @note Includes basic checks to ensure the sensor is properly initialized before reading data.
 * @see https://github.com/Arthur5492
 */

#ifndef DHT11_H
#define DHT11_H

#pragma once

#include <DHT.h>

class DHT11Sensor
{  
  public:
    DHT11Sensor() = default;
    ~DHT11Sensor(){};

    void setPIN(uint8_t pin);
    void read();
    bool dhtExists();
    
    int getTemperature() { return _temperature; };
    int getHumidity()    { return _humidity;    };
    
  private:
    uint8_t _pin;
    DHT *_dht = nullptr;

    int _temperature = 0;
    int _humidity = 0;
};

extern DHT11Sensor dht11;

#endif