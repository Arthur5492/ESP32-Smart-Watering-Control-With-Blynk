#ifndef WATERLEVEL_H
#define WATERLEVEL_H

#include <Arduino.h>

namespace waterLevel
{
  uint8_t pin_topLevel;
  uint8_t pin_bottomLevel;
  void setup(uint8_t PIN1,uint8_t PIN2)
  {
    pin_topLevel =    PIN1;
    pin_bottomLevel = PIN2;

    pinMode(pin_topLevel, INPUT);
    pinMode(pin_bottomLevel, INPUT);
  }

  /// @brief  Verifica se o tanque esta vazio(Quando o sensor inferior estiver LOW)
  /// @return Retorna true se o sensor inferior estiver LOW
  bool isLow()
  {
    return digitalRead(pin_bottomLevel) == LOW;
  }


  /// @brief Verifica se o tanque esta cheio(Quando o sensor superior estiver HIGH)
  /// @return Retorna true se  o sensor superior estiver HIGH
  bool isFull()
  {
    return digitalRead(pin_topLevel) == HIGH; 
  }

  /// @brief Liga motor de agua ate que o sensor de nivel de agua superior for HIGH 
  /// @param PIN_WATERPUMP - Pino do motor de agua 
  void fillTank(uint8_t PIN_WATERPUMP)
  {
    unsigned long startTime = millis();
    unsigned long tempoPercorrido = 0; //?Sera q vale a pena enviar pro blynk?
    digitalWrite(PIN_WATERPUMP, HIGH);
    Serial.printf("Enchendo tanque de agua \n");
    while(waterLevel::isFull() != true)
    {
      tempoPercorrido = millis();
      tempoPercorrido = tempoPercorrido - startTime;
      Serial.printf("Tempo percorrido: %.2f\n",tempoPercorrido);
    };
    
    Serial.printf("Tanque cheio!\n\n Tempo total percorrido: %.3f"
                  ,tempoPercorrido);

    Serial.printf("Desligando bomba de agua... \n");
    digitalWrite(PIN_WATERPUMP, LOW);
  }

}




#endif
