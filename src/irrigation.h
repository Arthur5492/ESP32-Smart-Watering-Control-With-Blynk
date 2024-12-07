/**
 * @file irrigation.h
 * @brief Controls the irrigation system, managing water pump activation and integrating data from various sensors.
 * @details Implements thresholds for soil moisture, temperature, and humidity to ensure efficient irrigation.
 *          Handles critical errors and provides overrides for testing and forced operation.
 * @note Logic prioritizes soil moisture, with additional safeguards for temperature limits.
 * @see https://github.com/Arthur5492
 */
#ifndef IRRIGATION_H
#define IRRIGATION_H

#pragma once

#include "soilMoisture.h"
#include "dht11.h"
#include "waterTankManager.h"

class Irrigation
{
  public:
    Irrigation()  {turnOffPump(); };
    
    /// @brief Run entire logic
    /// @param forceRun true: Run ignoring critical Issues / false: stop logic if having Issues
    void run(bool forceRun = false);

    void setPumpPIN(uint8_t waterPumpPin);
    void turnOnPump();
    void turnOffPump();

    //Logic
    void getSensorsData();
    void checkTemperatureLimit(); 
    void testHumidityVariation();

    //Getters
    bool getIsIrrigating()  { return _isIrrigating; };
    bool get_criticalError(){ return criticalError; };

    /// @brief Defines DHT11 Humidity value for irrigation logic
    /// @param humThres humidity interger 0-100
    void setHumThreshold(uint8_t humThres) {_humidityThreshold = humThres; };

    /// @brief Defines DHT11 Temperature max value for irrigation logic
    /// @param tempThres temperature interger 0-255
    void setTempThreshold(uint8_t tempThres)    {_temperatureThreshold = tempThres; };

    /// @brief Defines Soil Moisture minimal humidity percentage value
    /// @param minsoilThres Moisture interger 0-100 (percentage)
    void setSoilMostureMin(uint8_t minsoilThres) { _soilMoistureMinHumidity = minsoilThres; };

    /// @brief Defines Soil Moisture max(ideal) humidity Percentage value
    /// @param maxsoilThres Moisture interger 0-100 (percentage)
    void setSoilMostureMax(uint8_t maxsoilThres) { _soilMoistureMaxHumidity = maxsoilThres; };

  private:
    int _humidity = 0;
    int _temperature = 0;
    int _soilMoistureValue = 0;

    uint8_t _pinWaterPump;
    bool _isIrrigating = false;

    bool criticalError = false;
    
    int _humidityThreshold = -1; //?Nao achei uso pratico de humidade do dht11
    int _temperatureThreshold = 35;

    int _soilMoistureMinHumidity = 40;
    int _soilMoistureMaxHumidity = 50;
    int _soilMoistureLimit = 0;
    uint8_t _soilMoistureOffset = 5;

    unsigned long startTime = 0;
    unsigned long elapsedTime = 0;
    const unsigned long MAX_IRRIGATION_TIMEOUT = 60000;
};

extern Irrigation irrigationSystem;

#endif