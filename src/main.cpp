#include "wifiSetup.h"


//SENSORS
#include "dht11.h"
#include "waterTankManager.h"
//END SENSORS

void setup() { 
  Serial.begin(9600);
  
  ///      PINS SETUP      ///
  waterTank.setPINS(27,26,25);
  dht11.setPIN(22);
  //? waterPump, soil_mosture
  ///      PINS SETUP      ///

  acessPoint.begin();

  if(WiFi.isConnected()) 
    blynkHandler.config();
}

void loop() {
  //Acess Point to connect to wifi by captive portal
  acessPoint.loop(); 
  
  //Blynk will not always be connected, and we need the logic always running regardless of Blynk
  if(Blynk.connected()) 
  {
    Blynk.run();
    blynkHandler.publishData();  
  }
  
  waterTank.update();

  delay(100);
}
