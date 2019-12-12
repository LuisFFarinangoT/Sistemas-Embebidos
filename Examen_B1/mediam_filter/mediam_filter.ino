
#include "datos_sensor.h"
int Filter_Value;
#define FILTER_N 90
void setup () {
  Serial.begin (9600); 
 }

void loop () {
  Filter (); 
}

// Método de filtro mediano

float Filter () {
  float filter_buf [FILTER_N];
  int i, j;
  float filter_temp = 0;
  for (int k = 0; k < FILTER_N; k ++) {
    filter_buf[k] = 0;
    //Serial.println(filter_buf[i]);
    delay (10);
  }
  for (i = 0; i < FILTER_N; i ++) {
    filter_buf[i] = temperatura[i];
    //Serial.println(filter_buf[i]);
    delay (10);
  }
  // los valores de muestra se ordenan en orden ascendente (método de burbuja)
  for (j = 0; j < FILTER_N ; j ++) {
    for (i = j + 1; i < FILTER_N  ; i ++) {
      if (filter_buf[j] > filter_buf [i]) {
        filter_temp = filter_buf[j];
        filter_buf[j] = filter_buf [i];
        filter_buf[i] = filter_temp;
        Serial.print(filter_buf [i] );
        delay(20);
        Serial.print(",");
        Serial.println(temperatura[i]);
        delay(20);
      }
    }filter_temp=0;
    
  }

}
