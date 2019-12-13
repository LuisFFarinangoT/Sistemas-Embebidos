#include "datos_sensor.h"
void setup() {
  Serial.begin(9600);
}
void loop() {
  int temperatura[88];
  int i, j, k, temp;
  int tamano = 3;
  int vector[3];
  int vecmed[198];
  
for (k = 0; k < 88; k++){ 
vector[0] = temperatura[k];
  vector[1] = temperatura[k + 1];
  vector[2] = temperatura[k + 2];
  for (i = 0; i < (tamano - 1); i++){
   for (j = i + 1; j < tamano; j++){
     if (vector[j] < vector[i]){
       temp = vector[j];
        vector[j] = vector[i];
        vector[i] = temp;
      }
    }
  }
  vecmed[k] = vector[1];
}
//Serial.print("\nLas medianas son:\n");
for (i = 0; i < 88; i++)
{
  Serial.print( temperatura[i]);
  delay(10);
  Serial.print(",");
  Serial.println( vecmed[i]);
  delay(20);
}
}
