#ifndef DHT11_H
#define DHT11_H

#include <DHT.h>

class DHT11Sensor
{  
  private:
    uint8_t PIN = 5;
    DHT dht;

    float temperature;
    float humidity;

  public:
    DHT11Sensor(): dht(PIN,DHT11){ dht.begin(); };
    ~DHT11Sensor(){};


    float getTemperature();
    float getHumidity();

};

extern DHT11Sensor dht11;

#endif