#ifndef BLYNK_H
#define BLYNK_H

#define BLYNK_TEMPLATE_ID "TMPL2toVcVWoG"
#define BLYNK_TEMPLATE_NAME "esp32 Devkit "
#define BLYNK_AUTH_TOKEN "SuPryZCKibYvAwgd1fXlBytIudbwGUAV"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>
#include <wifiSetup.h>
#include <dht11.h>

//           Blynk Input Pins       //
#define vblynk_dht11_temp    V0
#define vblynk_dht11_humi    V1
#define vblynk_captivePortal V2
#define vblynk_waterSensor   V3
//V0 = Botao virtual Temperatura DHT11
//V1 = Botao virtual Umidade DHT11
//V2 = Botao virtual Botão para ligar o Captive Portal
//V3 = Botao virtual Led para indicar agua

/////////////////////////////////////
//           Send Data to Blynk       //
void sendSensorsData()
{
  //DHT11 
   Blynk.virtualWrite(vblynk_dht11_temp, dht11.getTemperature());
   Blynk.virtualWrite(vblynk_dht11_humi, dht11.getHumidity());
  //END DHT11
  //SOILMOSTURE
  //->
  //END SOILMOSTURE
  Serial.print("Dados enviados ao Blynk");
}
/////////////////////////////////////
//          Get Data from Blynk          //
BLYNK_WRITE(vblynk_captivePortal)//Receive data from button inside Blynk
{
  int buttonState = param.asInt();

  if(buttonState == 1) 
  {
    Serial.print("Botão Blynk do Portal Acess ligado");
    digitalWrite(2, HIGH);
    acessPoint.startCaptivePortal();
  }
  else
  {
    acessPoint.logoutCaptivePortal();
    digitalWrite(2, LOW);
    Serial.print("Botão Blynk do Portal Acess desligado");
  }
  
}

/////////////////////////////////////
//           Blynk Timers       //
//https://docs.blynk.io/en/blynk-library-firmware-api/blynk-timer
BlynkTimer sensorTimer; 
//Endtimer

/// @brief Namespace to simplify Blynk usage
namespace blynkHandler
{

  void config();  //Config Blynk and Timers
  
  void config()
  {
    Blynk.config(BLYNK_AUTH_TOKEN);
    Blynk.connect();

    sensorTimer.setInterval(1000L, sendSensorsData);
  }
}

#endif