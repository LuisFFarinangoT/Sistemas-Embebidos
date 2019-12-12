#include "Type4051Mux.h"//libreria para el uso del mux. 
#include <OneWire.h>//libreria complementaria para el sensor de temperatura.
#include <DallasTemperature.h>//libreria para el sensor de temperatura.
#define ONE_WIRE_BUS 0 //Se establece el pin D3 como bus OneWire.
Type4051Mux sensor(A0, INPUT, ANALOG, 14, 12, 13);//declaracion de pines de control del mux.
OneWire oneWire(ONE_WIRE_BUS);//declaracion del pin del sensor de temperatura.
DallasTemperature sensors(&oneWire); //Se declara una variable u objeto para nuestro sensor
float voltaje = 5;//variable de led
//variable para kalman 
float varVolt = 1.12184278324081E-05;// varianza determinada por una hoja de excel 
float varProcess = 1e-8;
float Pc = 0.0;
float G = 0.0;
float P = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xe = 0.0;
void setup() {
  Serial.begin(9600); // Inicializamos comunicación serie.
  Serial.println("CONDICIONES DEL AGUA");
  Serial.println(" T° | pH | uS | NTU");
}
void loop() {
  Serial.print(temperatura());
  Serial.print(" | ");
  Serial.print(pH(0));
  Serial.print(" | ");
  Serial.print(tds(2));
  Serial.print(" | ");
  Serial.print(turbidez(5));
  Serial.println(" ");
  
}
float temperatura() { //MÉTODO DE TEMPERATURA
  sensors.requestTemperatures(); //obtener del sensor el valor de la temperatura
  float valortemp = sensors.getTempCByIndex(0);
  //karnal(valortemp);
  return valortemp;
}
float pH(int pin) { //MÉTODO DE PH
  float valorph, b, calibration = 7.3, buf[10], temp, sensorValue = 0;
  unsigned long int avgValue;
  for (int i = 0; i < 10; i++) {
    buf[i] = sensor.read(pin);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];
  float pHVol = (float)avgValue * voltaje / 1024 / 6;
  float phValue = -5.70 * pHVol + calibration;
  //karnal(phValue);
  return phValue;
}

float tds(int pin) { //MÉTODO DE CALIDAD
  float valortds, resistorValue = 10000.0, returnVoltage = 0.0, resistance = 0.0,
                  threshold = 3.0, analogValue = 0.0, oldAnalogValue = 1000.0;
  float TDS = 0.0;
  analogValue = sensor.read(pin);
  returnVoltage = analogValue * voltaje / 1024;
  resistance = ((voltaje * resistorValue) / returnVoltage) - resistorValue;
  valortds = 1.0 / (resistance / 1000000);
  TDS = 500 * (valortds / 100);
  //karnal(valortds);
  return valortds;
}
float turbidez(int pin) { //MÉTODO DE TURBIDEZ
  float volt, NTU, valorturbidez;
  valorturbidez = sensor.read(pin);
  volt = valorturbidez * (voltaje / 1023.0);
  NTU = (285.48 * pow(volt, 2)) - 2285.5 * volt + 4574.8;
  float NTUC = NTU / 1000.00;
  //karnal(NTUC);
  return NTUC;
}
void karnal(float voltage) {
  Pc = P + varProcess;
  G = Pc/(Pc + varVolt);// ganancia de kalman 
  P = (1-G)*Pc;
  Xp = Xe;
  Zp = Xp;
  Xe = G*(voltage-Zp)+Xp;// la estimacion de kalman para el sensor en cuestion .
 // serialFloatPrint(voltage);
  //serialFloatPrint(Xe);
  Serial.print(voltage*1000);
  Serial.print(' ');
  Serial.println(Xe*1000);
  //delay(20);
}
