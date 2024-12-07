/**
 * @file waterTankManager.h
 * @brief Provides logic to monitor and control water levels in a tank using sensor data and solenoid control.
 * @details This class implements water level detection with top and bottom sensors, manages solenoid operation
 *          for filling the tank, and includes mechanisms for handling critical errors like sensor failures.
 * @note Includes a timeout mechanism to prevent continuous filling in case of sensor malfunction or unexpected conditions.
 * @see https://github.com/Arthur5492
 */


#ifndef WATERTANKMANAGER_H
#define WATERTANKMANAGER_H
#pragma once

#include <Arduino.h>


enum TankState
{
    WTANK_LOW,
    WTANK_MID,
    WTANK_FULL,
    WTANK_ERROR
};

extern const char* TankStateString[];

class WaterTankManager {
public:
    WaterTankManager(){ stopFilling();};

    /// @brief Runs entire logic
    /// @param forceRun true: Run ignoring critical Issues / false: stop logic if having Issues
    void run(bool forceRun = false);

    /// @brief Check WaterLevel Sensor state
    /// @return true: sensor is HIGH / false: Sensor is LOW 
    bool checkWaterLevelSensor(unsigned int pin);
    
    /// @brief Determines the overall state of the water tank
    void checkWaterTankState();

    void startFilling();
    void stopFilling();



    ///GETTERS
    unsigned long getIsFilling()     { return _isFilling;                  };
    TankState getTankState()         { return _tankState;                  };
    const char* getStringTankState() { return TankStateString[_tankState]; };
    bool get_criticalError()         { return criticalError;               };
    bool get_topSensor()             { return topSensor;                    };
    bool get_botSensor()             { return botSensor;                    };
    ///END GETTERS

    ///SETTERS
    void setWaterLevelPins(uint8_t pinTopLevel, uint8_t pinBottomLevel);
    void setSolenoidPin(uint8_t pinSolenoid);
    /// @param timeout timeout in milliseconds
    void set_FILL_TIMEOUT(unsigned long timeout) {FILL_TIMEOUT = timeout; };
    ///END SETTERS
    
private:
    
    uint8_t _pinTopLevel;
    uint8_t _pinBottomLevel;
    uint8_t _pinSolenoid;

    bool topSensor = false;
    bool botSensor = false;
    bool _isFilling = false;
    TankState _tankState = WTANK_FULL;
    bool criticalError = false;

    unsigned long startTime = 0;
    unsigned long elapsedTime = 0;
    unsigned long FILL_TIMEOUT = 60000;
};

extern WaterTankManager waterTank;

#endif
