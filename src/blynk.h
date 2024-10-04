#ifndef BLYNK_H
#define BLYNK_H

#define BLYNK_TEMPLATE_ID "TMPL2toVcVWoG"
#define BLYNK_TEMPLATE_NAME "esp32 Devkit "
#define BLYNK_AUTH_TOKEN "SuPryZCKibYvAwgd1fXlBytIudbwGUAV"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>
#include <wifiSetup.h>
#include <dht11.h>

/////////////////////////////////////
//           Blynk Output Functions       //
void sendSensorsData()
{
  //DHT11
  Blynk.virtualWrite(V1, dht11.getHumidity());
  Blynk.virtualWrite(V2, dht11.getTemperature());
  //END DHT11
  //Water Level
}

/////////////////////////////////////
//           Blynk Input Pins       //
//V0 = Temperatura DHT11
//V1 = Umidade DHT11
//V2 = Botão para ligar o Captive Portal
//V3 = Led para indicar agua

BLYNK_WRITE(V2)
{
  int buttonState = param.asInt();

  if(buttonState == 1) //Ligar captive portal
  {
    digitalWrite(2, HIGH);
    acessPoint.startCaptivePortal();
  }
  else
  {
    acessPoint.logoutCaptivePortal();
    digitalWrite(2, LOW);
  }
}

/////////////////////////////////////
//           Blynk Timers       //
BlynkTimer sensorTimer;

namespace blynkHandler
{

  void loadTimers(); //setup timers
  void config();  //Config Blynk and set up timers
  void run(); ///Run Blynk Object and all Timers 

  

  void config()
  {
    Blynk.config(BLYNK_AUTH_TOKEN);
    Blynk.connect();

    loadTimers();
  }

  
  void loadTimers()
  {
    sensorTimer.setInterval(1000L, sendSensorsData);
  }  

  
  void run()
  {
    Blynk.run();
    sensorTimer.run();
  }

}

#endif