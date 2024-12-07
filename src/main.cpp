//Insert your Template ID and Template Name
#include "wifiSetup.h"
#include "waterTankManager.h"
#include "irrigation.h"
#include "blynkHandler.h"

unsigned long timer = 0;
#define BOOT_BUTTON 0
void setup() { 
  Serial.begin(9600);
  pinMode(2,OUTPUT); //Built-in LED
  pinMode(BOOT_BUTTON,INPUT_PULLUP); //BOOT BUTTON

  //PINS
  waterTank.setWaterLevelPins(18,19);
  soilMoisture.setPIN(34);
  dht11.setPIN(33);
  waterTank.setSolenoidPin(14);
  irrigationSystem.setPumpPIN(27);
  //ENDPINS

  //IRRIGATION PARAMETERS
  irrigationSystem.setSoilMostureMin(5);
  irrigationSystem.setSoilMostureIdeal(15);
  irrigationSystem.setHumThreshold(35);
  irrigationSystem.setTempThreshold(25);
  //END IRRIGATION PARAMETERS

  //TIMEOUT PARAMETERS
  waterTank.set_FILL_TIMEOUT(60000);
  irrigationSystem.set_IRRIGATION_TIMEOUT(60000);
  //END TIMEOUT PARAMETERS

  wifiSetup.begin();
  
  if(WiFi.isConnected()) 
    blynkHandler.config();

}

void loop() {
  
  wifiSetup.loop(); 

  if(Blynk.connected()) 
    blynkHandler.publishData();
  
  if(millis() - timer >= 2000) //Simpliest Timer to reduce amount of checks per iteration
  {
    waterTank.run();
    irrigationSystem.run();
    timer = millis();

    // Serial.printf("Sensor Topo: %d\n",waterTank.get_topSensor());
    // Serial.printf("Sensor Fundo: %d\n",waterTank.get_botSensor());
    // Serial.printf("Estado do Tanque: %s\n", waterTank.getStringTankState());
    // Serial.printf("Estado irrigacao: %d\n",irrigationSystem.getIsIrrigating());
    // Serial.printf("Temperatura: %d\n", dht11.getTemperature());
    // Serial.printf("Humidade Solo: %d\n",soilMoisture.getPercentValue());
  }

  if(digitalRead(BOOT_BUTTON) == LOW) //reset wifi stored by clicking boot button
  {
    wifiSetup.clearNVS();
    esp_restart();
  }

  
}
