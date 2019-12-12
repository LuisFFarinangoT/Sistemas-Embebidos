#include "matrizprueba.h"
int x ;//variables de conteo 
int y ;//variables de conteo 
float sumaph = 0;//variable que guarda el promedio de ph
float sumatem = 0;//variable que guarda el promedio de temperatura
float sumatds = 0;//variable que guarda el promedio de tds
float sumatur = 0;//variable que guarda el promedio de turbidez
float matrizerrores[120][6];//matriz que guarda el valor de error relativo
float matrizerroresabs[120][6];//matriz que guarda el valor de error relativo
void setup() {
  Serial.begin(9600);
  Serial.println("Matriz de error relativo ");
  Serial.print("temperatura");
  Serial.print("  |  ");
  Serial.print("pH");
  Serial.print("  |  ");
  Serial.print("tds");
  Serial.print("  |  ");
  Serial.print("turbidez");
  Serial.println("   ");
  for (x = 0; x < 120; x++) {//se llena la matriz de ceros 
    for (y = 0; y < 4; y++) {
      matrizerrores[x][y] = 0;
    }
  }
  for (x = 0; x < 120; x++) {//se llena la matriz de ceros 
    for (y = 0; y < 4; y++) {
      matrizerroresabs[x][y] = 0;
    }
  }
  for (x = 0; x < 120; x++) {//se calcula el promedio de cada medicion
    sumaph = sumaph + matrizprueba[x][0] / 120;
    sumatem = sumatem + matrizprueba[x][1] / 120;
    sumatds = sumatds + matrizprueba[x][2] / 120;
    sumatur = sumatur + matrizprueba[x][3] / 120;
  }

}
void loop() {
  delay(1000);
  for (x = 0; x < 120; x++) {//calculo de error relativo 
    matrizerrores[x][0] = matrizprueba[x][0] - sumaph;
    matrizerrores[x][1] = matrizprueba[x][1] - sumatem;
    matrizerrores[x][2] = matrizprueba[x][2] - sumatds;
    matrizerrores[x][3] = matrizprueba[x][3] - sumatur;
  }
  delay(1000);
  for (int d = 0; d < 120; d++) {//impresion de matriz de error relativo 
    for (int f = 0; f < 4; f++) {
      Serial.print(matrizerrores[d][f]);
      Serial.print("                ");
    }
    Serial.println(" ");
  }
  delay(1000);
  for (int g = 0; g < 120; g++) {//calculo de error absoluto de la medicion 
    matrizerroresabs[g][0] = matrizerrores[g][0]/ sumaph * (100 );
    matrizerroresabs[g][1] = matrizerrores[g][1] / sumatem* (100 );
    matrizerroresabs[g][2] = matrizerrores[g][2] / sumatds* (100 );
    matrizerroresabs[g][3] = matrizerrores[g][3] / sumatur* (100 );
  }
  delay(1000);
  Serial.println("Matriz de error absoluto ");//impresion de la matriz de error absoluto
  for (int p = 0; p < 120; p++) {
    for (int q = 0; q < 4; q++) {
      Serial.print(matrizerroresabs[p][q]);
      Serial.print("                ");
    }
    Serial.println(" ");
  }
  delay(20000);
}
