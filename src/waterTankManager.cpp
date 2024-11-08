#include "waterTankManager.h"

WaterTankManager waterTank;

/// @brief Set pins
/// @param pinTopLevel Water sensor in the top
/// @param pinBottomLevel Water sensor in the bottom
/// @param pinSolenoid //Water pump pin
void WaterTankManager::setPINS(uint8_t pinTopLevel, uint8_t pinBottomLevel, uint8_t pinSolenoid) 
{
	  _pinTopLevel = pinTopLevel;
  pinMode(_pinTopLevel, INPUT);

	_pinBottomLevel = pinBottomLevel;
  pinMode(_pinBottomLevel, INPUT);

	_pinSolenoid = pinSolenoid;
	pinMode(_pinSolenoid, OUTPUT);
		
}

bool WaterTankManager::isLow() const 
{
	return (digitalRead(_pinBottomLevel) == LOW);
}

bool WaterTankManager::isFull() const 
{
	return digitalRead(_pinTopLevel) == HIGH;
}

/// Determines the overall state of the water tank
uint8_t WaterTankManager::waterTankState() {
    bool _isFull = isFull();
    bool _isLow  = isLow();

    // Verifica erro dos sensores: ambos ativados simultaneamente
    if (_isFull && _isLow)
        return WTANK_ERROR;
    
		if(_isFilling)
			return WTANK_FILLING;

    // Verifica se está cheio
    if (_isFull)
        return WTANK_FULL;

    // Verifica se está vazio
    if (_isLow)
        return WTANK_LOW;

    // Se nenhum dos sensores está ativado, assumimos que está em um nível intermediário
    return WTANK_MID;
}

void WaterTankManager::fillTank() 
{
	if (!_isFilling) 
	{
		startTime = millis();
		digitalWrite(_pinSolenoid, HIGH);
		Serial.println("Filling Water Tank...\n");
		_isFilling = true;
	}
}

void WaterTankManager::update() 
{
	//?Deixar no main ou aqui
	if(isLow() && !_isFilling )
  {
    Serial.printf("WaterTank is low, executing fillTank logic");
    fillTank();
  }

	if (_isFilling) 
	{
		unsigned long currentTime = millis();

		if(isFull())
		{
			digitalWrite(_pinSolenoid, LOW);
			_isFilling = false;	
			elapsedTime = millis() - startTime;
			Serial.printf("Water Tank full!\nElapsed Time: %.3f seconds\n", elapsedTime / 1000.0);
			Serial.println("Turning Off Solenoid... \n");
		}
		else if(currentTime - startTime >= MAX_FILL_TIMEOUT)
		{
			digitalWrite(_pinSolenoid, LOW);
			Serial.println("Error: MAX_FILL_TIMEOUT reached, Water Tank stoped filling. Check the System.");
			_isFilling = false;
		}	
	}
}

