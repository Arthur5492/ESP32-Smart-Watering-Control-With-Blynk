#include <dht11.h>

DHT11Sensor dht11;

void DHT11Sensor::setPIN(uint8_t pin)
{
  _pin = pin;
  if(_dht == nullptr)
  {
    _dht = new DHT(_pin, DHT11);
    _dht->begin();
    Serial.printf("DHT Inicializated \n");
  }
  else
  Serial.printf("DHT already allocated \n");
}

bool DHT11Sensor::dhtExists()
  {
    if(_dht != nullptr)
      return true;
    
    Serial.printf("DHT not allocated \n");
    return false;
  }

#ifndef TEST_MODE
  double DHT11Sensor::getTemperature()
  {
    if(dhtExists())
      return _dht->readTemperature();
    
    return NAN;
  }

  double DHT11Sensor::getHumidity()
  {
    if(dhtExists())
      return _dht->readHumidity();

    return NAN;
  }

  

#else
  // Modo de teste: valores aleatórios para simular o sensor
  double DHT11Sensor::getTemperature() {
    if(dhtExists())
      return 20.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / 10.0));// Gera uma temperatura aleatória entre 20.0 e 30.0 graus

    return NAN;    
  }

  double DHT11Sensor::getHumidity() {
    if(dhtExists())
      return 40.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / 20.0)); // Gera umidade aleatória entre 40.0 e 60.0%

    return NAN;
  }
  
#endif


