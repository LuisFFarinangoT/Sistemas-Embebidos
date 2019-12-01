/*UTN-FICA-CIERCOM 
 * SISTEMAS EMBEBIDOS 
 * LUIS FARINANGO
 * 
*/
//Teorema de bayes
/*saber cuantas etiquetas tiene el conjunto de datos
   el num de filas y de comulunas
   etiquetas =1,2,3
   P(1)=sumatoria de todos los elementos con la etiqueta 1 y se divide para el total de filas
   P(2)=sumatoria de todos los elementos con la etiqueta 2 y se divide para el total de filas
   P(3)=sumatoria de todos los elementos con la etiqueta 3 y se divide para el total de filas
   P(x)=sumatoria de los elementos dentro de la circunferencia y dividir para el total de filas
 *      *enontrar la circunferencia
                                  :distancia entre la nueva instancia y la base de datos
                                  :encontrar la mayor distancia y se divide para el resto de las distancias encontrados
                                  :Finalmente se define el radio entre 0 y 1
  P(x/1)=sumatoria de todos los elemntos de las circcunferencia con etiq 1 y se divide para el total de etiquetas 1
  P(x/2)=sumatoria de todos los elemntos de las circcunferencia con etiq 2 y se divide para el total de etiquetas 2
  P(x/3)=sumatoria de todos los elemntos de las circcunferencia con etiq 3 y se divide para el total de etiquetas 3

  Encontrar la probablilidad  con la formula
  P(1/x)=P(1)*P(x/1)/P(x)
  P(2/x)=P(2)*P(x/2)/P(x)
  P(3/x)=P(3)*P(x/3)/P(x)
  Finalmente se compara entre todas y se asigna la etiqueta
*/

#include "matrizentrenamiento.h"
float datos_prueba[5] = {5.9, 3, 5.1, 1.8,3}; //6,2  2,9 4,3 1,3
int conte ;
int valetiq = 0;
int resul;
int contep = 0;
float distancia = 0;
float distanciam = 0.1;
int contpro1 = 0;
int contpro2 = 0;
int contpro3 = 0;
float probx = 0;
float probn = 0;
float auxi = 0.1;
float etiquetaf;
void setup() {
  Serial.begin(9600);
}
void loop() {

  bayesiano(3, 4, 3, 0.2);
  delay (500);
}

void bayesiano (int etiquetas , int columnas, int filas, float r) {
  /*la matriz se va a llenar de la siguente forma en el caso de tres etiquetas
        1       2       3     --------etiquetas
      sum1    sum2    sum3    ------sumatorias
      P(x/1)  P(x/2)  P(x/3)  -----sumatoria de circunferencias
      P(1/x)  P(2/x)  P(3/x)  ----probabilidades obtenidas
  */
  int i = 0;
  int j = 0;
  int k = 0;
  float suma = 0;
  float matrizb[4][etiquetas];
  float numetiq[etiquetas ];
  float norma[120];
  probn = probn / 120;
  for (i = 0; i < 4; i++) {//lenado de ceros de la matriz de trabajo .
    for (j = 0; j < etiquetas; j++) {
      matrizb[i][j] = 0;
      //Serial.print(matrizb[i][j]);
      //Serial.print(' ' );
    }
    //Serial.println(' ' );
  }

  for (int e = 0; e < 120; e++) {//calculo de distancia mayor
    for (int d = 0; d < 4 ; d++) {
      suma = suma + pow(matriz[e][d] - datos_prueba[d], 2);
    }
    distancia = sqrt(suma);
    //se elije a la distancia mayor
    if (distancia > distanciam) {
      distanciam = distancia;
    }
    //Serial.println(distancia,4);
    distancia = 0;//reseteo
    suma = 0;
  }
  for (int m = 0; m < 120; m++) {//normalizacion de los datos obtenidos
    for (int n = 0; n < columnas ; n++) {
      suma = suma + pow(matriz[m][n] - datos_prueba[n], 2);
      distancia = sqrt(suma) / distanciam; //se normaliza los datos
      if (distancia < r)//se encuentra los valores que entran en el radio
      { norma[m] = 1;
      } else
      { norma[m] = 0;
      }
    }
    //Serial.println(norma[m], 4);
    distancia = 0;
    suma = 0;
  }
  for ( i = 0; i < 120 ; i++) {//se obtiene las etiquetas y numero de etiquetas de la matriz de entrenamiento
    if (matriz[i][4] == matriz[i + 1][4]) //condicion de conteo
    { conte++;//aumento de contador
      delay(10);
    }
    else {//condicion si la etiqueta cambia
      contep++;
      resul = conte + 1;
      probn = resul;
      matrizb[0][contep - 1] = contep;
      matrizb[1][contep - 1] = resul;
      conte = 0;
      if (contep == etiquetas)
      {
        i = 3000;
        contep = 0;
      }
    }
  }
  for (; k < 120; k++) {//se calcula P(x/1),P(x/2),P(x/3)
    if (k == 119)//se resetea los contadores cuando se haya finalizado de revisar el vector
    { probx = float(contpro1 + contpro2 + contpro3) / 120;
      contpro1 = 0;
      contpro2 = 0;
      contpro3 = 0;
    }
    if (k >= 0 && k < 40)//se analiza la primer etiqueta
    {
      if (norma[k] == 1) {
        contpro1++;
        matrizb[2][0] = contpro1;
      }
    }
    else if (k >= 41 && k < 80) {//se analiza la segunda etiqueta
      if (norma[k] == 1) {
        contpro2++;
        matrizb[2][1] = contpro2;
      }
    }
    else if (k >= 80 && k < 120) {//se analiza la tercer  etiqueta
      if (norma[k] == 1) {
        contpro3++;
        matrizb[2][2] = contpro3;
      }
    }
  }
  for (i = 0; i < 3; i++) {//se obtiene la probabilidad
    matrizb[2][i] = matrizb[2][i]/40;
  }
  for (j = 0; j < 3; j++) { //se obtiene la probabilidad final
    matrizb[3][j] = ((matrizb[2][j]) * (probn / 120)) / (probx);
  }

  for (i = 0; i < 4; i++) {//impresion de la matriz obtenida
    for (j = 0; j < etiquetas; j++) {
      Serial.print(matrizb[i][j], 4);
      //Serial.print(matrizb[i][j]);
      Serial.print(' ');
    }
    Serial.println(' ');
  }
  Serial.println(' ');
  for (int g = 0; g < 3; g++) {
    if (matrizb[3][g] > auxi) {
      auxi = matrizb[3][g];
      etiquetaf = g;
    }
  }
  Serial.print("La etiqueta es ");//impresion de resultados 
  switch(int(etiquetaf))
  { case 0:
      Serial.print("setosa");
      break;
    case 1:
      Serial.print("versicolor");
      break;
    case 2:
      Serial.print("virginica");
      break;
  }
  //Serial.println(etiquetaf);
}
