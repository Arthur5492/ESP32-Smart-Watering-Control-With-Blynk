#include "irrigation.h"

Irrigation irrigationSystem;

void Irrigation::run(bool forceRun)
{
  if(!forceRun && criticalError)
  {
    Serial.println("Water Pump timeout reached, check the Soil Moisture sensor and reboot the system\n");
    digitalWrite(2,HIGH);
    turnOffPump();
    return;
  }
  
  getSensorsData();

  checkTemperatureLimit();

  if(_soilMoistureValue <= _soilMoistureLimit && _isIrrigating == false && waterTank.getTankState() != WTANK_LOW)
    turnOnPump();
  
  if(_isIrrigating)
  {
    unsigned long currentTime = millis();

    if(waterTank.get_criticalError())
    {
      turnOffPump();
      return;
    }

    if(_soilMoistureValue >= _soilMoistureMaxHumidity)
    {
      turnOffPump();
      elapsedTime = (currentTime - startTime);
      Serial.printf("Irrigation Completed! \n Elapsed time: %.2f seconds\n", elapsedTime/1000.0);
    }
    else if(currentTime - startTime >= MAX_IRRIGATION_TIMEOUT)
    {
      turnOffPump();
      criticalError = true;
      Serial.printf("Error: MAX_IRRIGATION_TIMEOUT: %.2f seconds reached, Water Pump stopped irrigating. Check the System. \n", MAX_IRRIGATION_TIMEOUT/1000.0);
    }
  }
}

void Irrigation::turnOnPump()
{
  digitalWrite(_pinWaterPump,LOW);
  _isIrrigating = true;
  startTime = millis();
  Serial.println("Turning on Water Pump... \n");
}

void Irrigation::turnOffPump()
{
  digitalWrite(_pinWaterPump, HIGH);
  _isIrrigating = false;
  Serial.println("Turning off Water Pump... \n");
}

void Irrigation::getSensorsData()
{
  dht11.read(); 
  soilMoisture.read();
  
  _humidity = dht11.getHumidity();
  _temperature = dht11.getTemperature();
  _soilMoistureValue = soilMoisture.getPercentValue();
}

void Irrigation::checkTemperatureLimit()
{
  if(_temperature >= _temperatureThreshold)
    _soilMoistureLimit = _soilMoistureMinHumidity + _soilMoistureOffset;
  else
    _soilMoistureLimit = _soilMoistureMinHumidity;
}

void Irrigation::setPumpPIN(uint8_t waterPumpPin) 
{
  _pinWaterPump = waterPumpPin; 
  pinMode(_pinWaterPump, OUTPUT);

  digitalWrite(_pinWaterPump,HIGH); //Ensure water pump starts off
};

void Irrigation::testHumidityVariation() //! EM TESTE
{
  Serial.println("Soil Moisture variation test: \n");
  int initialPercentage = soilMoisture.getPercentValue();
  turnOnPump();
  delay(5000);
  turnOffPump();
  int finalPercentage = soilMoisture.getPercentValue();

  int percentageDiff = finalPercentage - initialPercentage;
}

//Se Humidade de solo cair menos que _soilMoistureMinHumidity;
//Se temperatura for maior que 35ºC agua do solo evapora mais rapido  
//Temperatura ≤ 35°C: Deixa a humidade do solo cair até 40% antes de irrigar.
//Temperatura > 35°C: Irrigar quando a humidade do solo cair até 45%, pra compensar a evaporação rápida e proteger a planta do estresse térmico.
