/**
 * @file blynkHandler.h
 * @brief Handles communication with the Blynk IoT platform, sending sensor data and managing related configurations.
 * @details This file integrates the Blynk platform with other components
 *          It ensures efficient data publishing and provides functionality to configure the Blynk authentication token.
 * @author Arthur
 * @see Github https://github.com/Arthur5492
 */
#ifndef BLYNKHANDLER_H
#define BLYNKHANDLER_H
#pragma once

#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_NO_GLOBAL_INSTANCES
#define NO_GLOBAL_BLYNK

#include "blynkConfig.h"
#include "dht11.h"
#include "waterTankManager.h"
#include "soilMoisture.h"
#include "irrigation.h"

#include <BlynkSimpleEsp32.h>
#include <array>
enum BlynkPins
{
  DHT11_TEMP    = V0,
  SOIL_MOISTURE = V1,
  WATER_TANK    = V2,
  IRRIGATION    = V3,
  GENERAL_ERROR = V4
};



class BlynkHandler
{
  public:

    /// @brief Set Timers and Blynk Connection 
    bool config();

    //Send sensors data //!Warning: MAX 10 publishes per second
    // Learn more in: https://docs.blynk.io/en/blynk-library-firmware-api/limitations-and-recommendations
    void send_DHT11();
    void send_WaterTankState();
    void send_soilMoisture();
    void send_IrrigationState();
    void send_generalErrors();
    void send_AllData();
    void publishData();

  private:
    /// @note Learn more about Blynk Timer in:
    /// @link https://docs.blynk.io/en/blynk-library-firmware-api/blynk-timer
    BlynkTimer timer;   

    enum BlynkERROR {IRRIGATION_ERROR, SOILMOISTURE_ERROR, WATERTANK_ERROR, NO_ERROR};
    
    uint8_t errorIndex = 0;
    unsigned long lastSendTime = 0;

     
};

extern BlynkHandler blynkHandler;

#endif