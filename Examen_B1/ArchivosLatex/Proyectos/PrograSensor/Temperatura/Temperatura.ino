#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 0 //Se establece el pin D1 como bus OneWire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); //Se declara una variable u objeto para nuestro sensor
int led = D1;
int led1 = D2;
int boton = D4;
boolean state=LOW;
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(D2),button,RISING);
  pinMode(led,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(boton,INPUT);
}

void loop() {
  
//    digitalWrite(led,LOW);
//  digitalWrite(led1,HIGH);
//  sensors.requestTemperatures(); // Enviamos este comando para obtener del sensor el valor de la temperatura
//  float temp = sensors.getTempCByIndex(0);
//  Serial.println("Temperature is: ");
//  Serial.println(temp+2.00); // Podemos tener más de un sensor en el mismo bus, 0 se refiere al primer sensor del bus
//  delay(1000);
//  digitalWrite(led1,0);
//    digitalWrite(led,HIGH);
//  delay(1000);
}

void button(){
  Serial.print("Stamp(ms): ");
 Serial.println(millis());
}
