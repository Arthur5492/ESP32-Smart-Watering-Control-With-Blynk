#ifndef DHT11_H
#define DHT11_H

#pragma once

#include <DHT.h>

class DHT11Sensor
{  
  private:
    uint8_t _pin;
    DHT *_dht = nullptr;

    double temperature;
    double humidity;

  public:
    DHT11Sensor() = default;
    ~DHT11Sensor(){};

    void setPIN(uint8_t pin);
    double getTemperature();
    double getHumidity();
    bool dhtExists();
};

extern DHT11Sensor dht11;

#endif