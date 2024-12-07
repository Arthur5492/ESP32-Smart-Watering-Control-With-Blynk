#include <dht11.h>

DHT11Sensor dht11;

void DHT11Sensor::setPIN(uint8_t pin)
{
  _pin = pin;

  if(_dht)
    delete _dht;

  _dht = new DHT(_pin, DHT11);
  _dht->begin();  
  Serial.printf("DHT Inicializated \n");
  delay(100);
}

bool DHT11Sensor::dhtExists()
{
  if(_dht != nullptr)
    return true;
  
  return false;
}

void DHT11Sensor::read()
{
  if(dhtExists())
  {
    _temperature = _dht->readTemperature();
    _humidity    = _dht->readHumidity(); 
  }
}
  


