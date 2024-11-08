/**
 * @file waterTankManger.h
 * @brief Monitors and controls water levels in a tank.
 *
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
    WTANK_FILLING,
    WTANK_ERROR
};

class WaterTankManager {
public:
    WaterTankManager() = default;

    void setPINS(uint8_t pinTopLevel, uint8_t pinBottomLevel, uint8_t pinWaterPump);
    
    /// @brief checks when the bottom sensor is LOW
    bool isLow() const;

    /// @brief Checks when the top sensor is HIGH
    bool isFull() const;
    
    uint8_t waterTankState();
    void fillTank();
    void update();


    unsigned long isFilling() { return _isFilling; };

private:
    
    uint8_t _pinTopLevel;
    uint8_t _pinBottomLevel;
    uint8_t _pinSolenoid;

    bool _isFilling = false;
    unsigned long startTime = 0;
    unsigned long elapsedTime = 0;
    unsigned long MAX_FILL_TIMEOUT = 15000;
};

extern WaterTankManager waterTank;

#endif
