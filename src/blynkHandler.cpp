#include "blynkHandler.h"

BlynkHandler blynkHandler;
  
WiFiClient _blynkWifiClient;
BlynkEsp32Client _blynkTransport(_blynkWifiClient);
BlynkWifi Blynk(_blynkTransport);

bool BlynkHandler::config()
{
  timer.setInterval(3000L,[this](){ send_AllData();});
  Blynk.config(BLYNK_AUTH_TOKEN); 
  if(Blynk.connect() == true)
    return true;
  
  return false;
}

void BlynkHandler::send_DHT11()
{
  Blynk.virtualWrite(DHT11_TEMP, dht11.getTemperature());
}

void BlynkHandler::send_soilMoisture()
{
  Blynk.virtualWrite(SOIL_MOISTURE, soilMoisture.getPercentValue());
}

void BlynkHandler::send_WaterTankState()
{
  Blynk.virtualWrite(WATER_TANK,waterTank.getTankState());
}


void BlynkHandler::send_IrrigationState()
{
  Blynk.virtualWrite(IRRIGATION, irrigationSystem.getIsIrrigating());
}

void BlynkHandler::send_generalErrors()
{
  unsigned long currentTime = millis();

  if(currentTime - lastSendTime >= 3000)
  {
    
    uint8_t errorValue = NO_ERROR;
    std::array<uint8_t,3> haveError = {NO_ERROR,NO_ERROR,NO_ERROR};

    if(irrigationSystem.get_criticalError())
      haveError.at(0) = IRRIGATION_ERROR;

    if(soilMoisture.getPercentValue() == 0)
      haveError.at(1) = SOILMOISTURE_ERROR;

    if(waterTank.get_criticalError())
      haveError.at(2) = WATERTANK_ERROR;
    

    //Get the atualIndex error if exists
    if(haveError.at(errorIndex) != NO_ERROR) 
      errorValue = haveError.at(errorIndex);
    else  
    {
      for(uint8_t i=0;i<haveError.size();i++)//Get any error that remains
      {
        if(haveError.at(i) != NO_ERROR)
        {
          errorValue = haveError.at(i);
          break;
        }
      }
    }
    
    lastSendTime = currentTime;

    if(errorIndex >=2)
      errorIndex = 0;
    else
      errorIndex++;

    Blynk.virtualWrite(GENERAL_ERROR, errorValue);
  }
}

void BlynkHandler::send_AllData()
{
  send_DHT11();
  send_soilMoisture();
  send_WaterTankState();
  send_IrrigationState();
  send_generalErrors();

  Serial.println("Data sent to Blynk Cloud!\n");
}

void BlynkHandler::publishData()
{
  Blynk.run();
  timer.run();
}

