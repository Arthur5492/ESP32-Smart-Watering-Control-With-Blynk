#include <wifiSetup.h>
#include <dht11.h>
#include <blynk.h>
#include <waterLevel.h>

void setup() { 
  Serial.begin(9600);
  
  acessPoint.begin();
  //Blynk
  blynkHandler::config();
  //END Blynk
}

void loop() {
  blynkHandler::run();

  acessPoint.loop(); //Acess Point to connect to wifi by captive portal

  if(waterLevel::isHIGH())
    Blynk.virtualWrite(V3, HIGH);
  else  
    Blynk.virtualWrite(V3, LOW);

}
