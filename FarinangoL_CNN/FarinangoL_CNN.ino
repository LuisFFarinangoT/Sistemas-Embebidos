#include "matrizentrenamiento.h"
float datos_prueba[5] = {6.2, 2.9, 4.3, 1.3, 2}; //vector de prueba
int respuesta;
int conte = 0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  int valre = tame(120, 4) + 1;//llamar al metodo de conteo de etiquetas en la matriz
  cnn(3, 5, 120, valre);//metodo de vecinos condensados
  //Serial.println(rep);
  //delay(5000);
}
int tame(  int tam_fil, int col_etiq)//metodo de conteo d etiquetas en la matriz de entrenamiento
{
  int resul;//variable que guarda el numero de etiquetas repetidas
  for (int i = 0; i < tam_fil - 1; i++) {//recorrido de la matriz
    // Serial.print(i);
    if (matriz[i][col_etiq] == matriz[i + 1][col_etiq])//condicion de conteo
    { conte++;//aumento de contador
      resul = conte;//se iguala el contador
      //Serial.print('-');
      //Serial.println(conte);
      delay(100);//retardo del sistema
    }
    else {//condicion si la etiqueta cambia
      conte = 0;
      return resul;//devuelve un entero
    }
  }
}

void cnn (int etiquetas, int tam_col, int tam_fil, int rep) {//metodo de cnn
  int i;//variable de conteo
  String compro;
  int j;//variable de conteo
  int l;//variable de conteo
  int col;//variable de conteo
  int fil;//variable de conteo
  String valc;//variable que guarda si es S o D
  float mresul;//variable que guarda en vector  si es S o D pero con equivalencias numericas
  float centroid = 0;//variable que guarda el calculo  de centriodes
  float sum1, sum2, sum3;//variable que guarda las sumas de cada centriode con la matriz de entrenamiento
  float dist1, dist2, dist3;//variable que guarda las distamcias  de cada centriode con la matriz de entrenamiento
  float competi = 0;//variable de comparacion de etiquetas
  float centroides [etiquetas][tam_col];//variable que guarda en matriz a los centriodes
  float  matrizaux [tam_fil ][tam_col + 1]; //matriz que guardara la nueva impresionn
  float cnnetiq[tam_fil] = {};//variable que guarda las etiquetas resultantes del metodo
  float centroide1[tam_col - 1] = {};//vector que guarda el centroide 1
  float centroide2[tam_col - 1] = {};//vector que guarda el centroide 2
  float centroide3[tam_col - 1] = {};//vector que guarda el centroide 3
  for (i = 0; i < etiquetas; i++) {//llenado de ceros de la matriz 
    for (j = 0; j < tam_col; j++) {
      centroides[i][j] = 0;
    }
  }
  for (l = 0; l < etiquetas; l++) {//se calcula la matriz de centroides 
    for (i = 0; i < tam_col - 1; i++) {
      for (j = (rep * l); j < rep * (l + 1); j++) {
        centroid = centroid + matriz[j][i];
      }
      centroides[l][i] = centroid / rep;
      //Serial.print(centroides[l][i]);
      //Serial.print(("  "));
      centroid = 0;
    }
    //Serial.println(' ');
    //centroide1[j] = centroides[2][i] ;
  }

  for (j = 0; j < tam_col - 1; j++) {//se separa cada centroide para su uso posterior 
    centroide1[j] = centroides[0][j] ;
    centroide2[j] = centroides[1][j] ;
    centroide3[j] = centroides[2][j] ;
    //    Serial.print(centroides[0][0]);
    //    Serial.print(' ');
    //    Serial.print(centroides[1][j]);
    //    Serial.print(' ');
    //    Serial.println(centroides[2][j]);
  }

  //  for (int i = 0; i < etiquetas; i++)
  //  { Serial.println(centroide1[i]);
  //  }


  /////////////////////////////////////////knn con matriz de entrenamiento
  for (fil = 0; fil < tam_fil; fil++) {//se recorre la matriz para sacar la distancia de cada centroide a la matriz
    for (col = 0; col < tam_col - 1; col++) { // menos 1 por ultima columna es etiqueta
      sum1 = sum1 + pow(matriz[fil][col] - centroide1[col], 2);
      sum2 = sum2 + pow(matriz[fil][col] - centroide2[col], 2);
      sum3 = sum3 + pow(matriz[fil][col] - centroide3[col], 2);
    }
    dist1 = sqrt(sum1);
    dist2 = sqrt(sum2);
    dist3 = sqrt(sum3);
    //    Serial.print(dist1);
    //    Serial.print(' ');
    //    Serial.print(dist2);
    //    Serial.print(' ');
    //    Serial.println(dist3);
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    // comparación de nuevo dato con solo la distacia mayor almacenada en matriz_k
    if (dist1 < dist2 && dist1 < dist3)//se compara las etiquetas para saber si se clasifico correctamente
    { competi = 1;
      cnnetiq[fil] = competi;
    }
    else if (dist2 < dist3 && dist2 > dist1) {
      competi = 2;
      cnnetiq[fil] = competi;
    }
    else if (dist3 > dist1 && dist3 > dist2) {
      competi = 3;
      cnnetiq[fil] = competi;
    }
    //Serial.println(cnnetiq[fil]);
    if (matriz[fil][4] == cnnetiq[i])//Comprobacion de etiqueta 
    { matrizaux[fil][4] = 10;// si es D

    }
    else
    { matrizaux[fil][4] = 12;//si es S
    }
    //Serial.println(sd[i]);
  }
  for (i = 0; i < tam_fil; i++) {//se guarda todo en una nueva matriz 
    for (j = 0; j < tam_col - 1; j++) { // menos 1 por ultima columna es etiqueta
      matrizaux [i][j] = matriz[i][j];
    }
  }
  for (i = 0; i < tam_fil; i++) {//Impresiones 
    for (j = 0; j < tam_col ; j++) { // menos 1 por ultima columna es etiqueta
      Serial.print(matrizaux [i][j] );
      Serial.print(' ');
    }
    Serial.println(' ');

  }
  Serial.println("Fin");
}
