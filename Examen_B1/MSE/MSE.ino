#include "matrizprueba.h"
//valor estimado de ph es 6.00
//valor estimado de temperatura es de 33.00
//valor estimado de tds  es de 1.6
//valor estimado de turbidez es de 4.3
int x ;//variables de conteo 
int y ;//variables de conteo 
float sumaph = 0;//variable que guarda el promedio de ph
float sumatem = 0;//variable que guarda el promedio de temperatura
float sumatds = 0;//variable que guarda el promedio de tds
float sumatur = 0;//variable que guarda el promedio de turbidez
float errorph=0;
float errortem=0;
float errortds=0;
float errortur=0;
float matrizerrores[120][6];//matriz que guarda el valor 
void setup() {
  Serial.begin(9600);
  Serial.println("El MSE es de  ");
  Serial.print("pH");
  Serial.print("  |  ");
  Serial.print("temperatura");
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
    matrizerrores[x][0] = matrizerrores[x][0]+(pow(matrizprueba[x][0] - 6.00,2));
    matrizerrores[x][1] = matrizerrores[x][1]+(pow(matrizprueba[x][1] - 32.00,2));
    matrizerrores[x][2] =matrizerrores[x][2]+(pow(matrizprueba[x][2] - 1.6,2));
    matrizerrores[x][3] = matrizerrores[x][3]+(pow(matrizprueba[x][3] - 4.3,2));
    errorph = sqrt((errorph + matrizerrores[x][0])/sumaph);
    errortem = sqrt((errortem + matrizprueba[x][1])/sumatem) ;
    errortds = sqrt((errortds + matrizprueba[x][2])/sumatds);
    errortur = sqrt((errortds + matrizprueba[x][3])/sumatur) ;
  }
  delay(1000);
  Serial.print(' ');
  Serial.print(errorph);
  Serial.print("      ");
  Serial.print(errortem);
  Serial.print("       ");
  Serial.print(errortds);
  Serial.print("       ");
  Serial.println(errortur);
  delay(20000);
  
}
