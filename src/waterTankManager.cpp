#include "waterTankManager.h"

WaterTankManager waterTank;

const char* TankStateString[] = 
{
    [WTANK_LOW] = "WTANK LOW",
    [WTANK_MID] = "WTANK MID",
    [WTANK_FULL] = "WTANK FULL",
    [WTANK_ERROR] = "WTANK ERROR"
};

void WaterTankManager::checkWaterTankState() {
    topSensor  = checkWaterLevelSensor(_pinTopLevel);
    botSensor = checkWaterLevelSensor(_pinBottomLevel);

    // Verifica erro dos sensores: ambos ativados simultaneamente
    if (topSensor && !botSensor)
			_tankState = WTANK_ERROR;

		else if(!topSensor && botSensor)
			_tankState = WTANK_MID;

    else if (topSensor && botSensor)
			_tankState = WTANK_FULL;

    else if (!topSensor && !botSensor)
			_tankState = WTANK_LOW;

	return;
}

void WaterTankManager::run(bool forceRun) 
{

	if(!forceRun && criticalError)
	{
			Serial.printf("Critical Water Level Sensor error, please reboot the system\n");
			stopFilling();
			digitalWrite(2,2); //blink built-in led on pin 2
			return;
	}

	checkWaterTankState();

	if(_tankState == WTANK_ERROR)
	{
		Serial.printf("WaterTank Sensor had problems please fix and restart the esp32 \n");
		stopFilling();
		criticalError = true;
		return;
	}
	
	if(_tankState == WTANK_LOW && !_isFilling )
  {
    Serial.printf("WaterTank is low, executing Filling logic \n");
    startFilling();
  }

	if (_isFilling) 
	{
		unsigned long currentTime = millis();

		if(_tankState == WTANK_FULL)
		{
			Serial.printf("Water Tank full!\n");
			stopFilling();
			elapsedTime = currentTime - startTime;
			Serial.printf("Elapsed Time: %.2f seconds\n", elapsedTime / 1000.0);
			return;
		}
		else if(currentTime - startTime >= FILL_TIMEOUT)
		{
			stopFilling();
			criticalError = true;
			Serial.printf("Error: FILL_TIMEOUT: %.2f seconds reached, Water Tank stoped filling. Please reboot the system. \n", FILL_TIMEOUT / 1000.0);
			return;
		}	
	}
}

/// @brief Set pins
/// @param pinTopLevel Water sensor in the top
/// @param pinBottomLevel Water sensor in the bottom
void WaterTankManager::setWaterLevelPins(uint8_t pinTopLevel, uint8_t pinBottomLevel) 
{
	  _pinTopLevel = pinTopLevel;
  pinMode(_pinTopLevel, INPUT_PULLUP);

	_pinBottomLevel = pinBottomLevel;
  pinMode(_pinBottomLevel, INPUT_PULLUP);
}

void WaterTankManager::setSolenoidPin(uint8_t pinSolenoid)
{
	_pinSolenoid = pinSolenoid;
	pinMode(_pinSolenoid, OUTPUT);

	digitalWrite(_pinSolenoid, HIGH); //Ensure Solenoid starts Off
}

bool WaterTankManager::checkWaterLevelSensor(unsigned int pin)
{
	bool sensorValue = LOW;

	if(digitalRead(pin) == HIGH)
		sensorValue = HIGH;
	else
		sensorValue = LOW;
	return sensorValue;
}

void WaterTankManager::startFilling() 
{
	if (!_isFilling) 
	{
		startTime = millis();
		digitalWrite(_pinSolenoid, LOW);
		Serial.println("Filling Water Tank...\n");
		_isFilling = true;
	}
	else
		Serial.println("ERROR: WaterTank is already filling\n");
}

void WaterTankManager::stopFilling()
{
		digitalWrite(_pinSolenoid, HIGH);
		_isFilling = false;		
		Serial.println("Solenoid turned off \n");
}

