#ifndef BLYNKTEST_H
#define BLYNKTEST_H
#pragma once

#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_TEMPLATE_ID "TMPL2toVcVWoG"
#define BLYNK_TEMPLATE_NAME "esp32 Devkit "
#define BLYNK_AUTH_TOKEN "SuPryZCKibYvAwgd1fXlBytIudbwGUAV"

#define NO_GLOBAL_BLYNK //Remove Blynk Global Instance(gives error if included outside main.cpp)

#include <BlynkSimpleEsp32.h>
#include <dht11.h>
#include <waterTankManager.h>

class BlynkHandler
{
  private:
    ///Learn more in: https://docs.blynk.io/en/blynk-library-firmware-api/blynk-timer
    BlynkTimer sensorTimer;    

  public:
  ///Blynk Digital Pins
  int DHT11_TEMP   = V0; int DHT11_HUM    = V1; 
  int SOIL_MOSTURE = V2; int WATER_TANK   = V3;
  int IRRIGATION   = V4; 
  
  void config();

  //Send sensors data //!Warning: MAX 10 writes per second
  void sendSensorsState();
  
  void send_WaterTankState();

  void publishData();
  
};

extern BlynkHandler blynkHandler;

#endif