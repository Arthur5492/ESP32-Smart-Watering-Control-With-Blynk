#include <wifiSetup.h>
#include <dht11.h>
#include <blynk.h>
#include <waterLevel.h>

#define PIN_WATERPUMP 12

void setup() { 
  Serial.begin(9600);
  
  acessPoint.begin();
  //Blynk
  blynkHandler::config();
  //END Blynk
}

void loop() {
  Blynk.run();
  sensorTimer.run();

  acessPoint.loop(); //Acess Point to connect to wifi by captive portal

  if(waterLevel::isLow())
    waterLevel::fillTank(PIN_WATERPUMP);
  
}
