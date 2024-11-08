#include "blynkHandler.h"

BlynkHandler blynkHandler;
  
WiFiClient _blynkWifiClient;
BlynkEsp32Client _blynkTransport(_blynkWifiClient);
BlynkWifi Blynk(_blynkTransport);

void BlynkHandler::config()
{
  sensorTimer.setInterval(1000L,[this](){ sendSensorsState(); });
  sensorTimer.setInterval(2000L,[this](){ send_WaterTankState(); });
  sensorTimer.setInterval(1000L,[this](){ send_WaterTankState(); });
  
  Blynk.config(BLYNK_AUTH_TOKEN); //!Colocar pra pegar no connectWifi
  Blynk.connect();
}

void BlynkHandler::sendSensorsState()
{
  Blynk.virtualWrite(DHT11_TEMP, dht11.getTemperature());
  Blynk.virtualWrite(DHT11_HUM, dht11.getHumidity());

}

void BlynkHandler::send_WaterTankState()
{
  uint8_t state = waterTank.waterTankState();
  Blynk.virtualWrite(WATER_TANK,state);
}

void BlynkHandler::publishData()
{
  send_WaterTankState();
  sendSensorsState();
}
