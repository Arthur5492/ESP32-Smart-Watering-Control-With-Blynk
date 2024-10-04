#include <dht11.h>

DHT11Sensor dht11;

float DHT11Sensor::getTemperature()
{
  dht.readTemperature();
  return temperature;
}

float DHT11Sensor::getHumidity()
{
  dht.readHumidity();
  return humidity;
}

