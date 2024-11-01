#include <dht11.h>

DHT11Sensor dht11;

float DHT11Sensor::getTemperature()  //Lê temperatura do sensor DHT11
{
  dht.readTemperature();
  return temperature;
}

float DHT11Sensor::getHumidity() //Lê umidade do sensor DHT11
{
  dht.readHumidity();
  return humidity;
}

