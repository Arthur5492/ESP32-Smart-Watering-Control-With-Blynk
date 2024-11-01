#include <Arduino.h>
#define Relay 26

void setup() {  //Teste relé 5V com motor bomba d'água
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
  
}

void loop() { //Liga e desliga o relé a cada 5 segundos
 
 digitalWrite(Relay, LOW);
 Serial.println("Relay ON");
 delay(5000);
 digitalWrite(Relay, HIGH);
 Serial.println("Relay OFF");
  delay(5000);
}
