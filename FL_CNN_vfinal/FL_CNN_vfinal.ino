#include "matrizentrenamiento.h"
float datos_prueba[5] = {6.2, 2.9, 4.3, 1.3, 2}; //6,2  2,9 4,3 1,3
int respuesta;
int conte = 0;

void setup() {
  Serial.begin(9600);
}
void loop() {
  int valre = tame(120, 4) + 1;//llamar al metodo de conteo de etiquetas en la matriz
  cnn(3, 5, 120, valre);//metodo de vecinos condensados
  //Serial.println(rep);
  delay(5000);
}
int tame(  int tam_fil, int col_etiq)//metodo de conteo d etiquetas en la matriz de entrenamiento
{
  int resul;
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
      conte = 0;//se vacia la variable de contador
      return resul;//devuelve un entero
    }
  }
}
void cnn (int etiquetas, int tam_col, int tam_fil, int rep) {//metodo de cnn
  int i;//variable de conteo
  int j;//variable de conteo
  int l;//variable de conteo
  int col;//variable de columnas de matriz entrenamiento
  int fil;//variable de filas de matriz entrenamiento
  float respaldo[col] = {};
  int s = 0; //contar los datos del source
  //float suma=0;
  int label;//variable que guarda la etiqueta
  float promedio = 0;//variable que guarda promedio 
  float distancia_menor = 3000;//variable de distancia menor 
  float distancia ;//variable de distancia total
  float centroid = 0;//variable de calculo de centroide
  /*
       centroides -> promedio
                     promedio por columna y por etiqueta
                     almaceno vectores
                     knn entre vectores y matriz de entrenamiento
  */
  float centroides [etiquetas][tam_col];//matriz de centroides
  for (i = 0; i < etiquetas; i++) {//conteo de matriz en columnas 
    for (j = 0; j < tam_col; j++) {//conteo de matriz en filas 
      if (j == (tam_col - 1)) {//se llena las etiquetas 
        centroides[i][j] = i + 1; //lenar etiqueta a cada centroide
      }
      else
      {//se llena las demas posiciones con ceros 
        centroides[i][j] = 0;
      }
    }
  }
  for (l = 0; l < etiquetas; l++) {//se llena la matriz de centroides 
    for (i = 0; i < tam_col - 1; i++) {
      for (j = (rep * l); j < rep * (l + 1); j++) {
        centroid = centroid + matriz[j][i];
      }
      centroides[l][i] = centroid / rep;
      //Serial.print(centroides[l][i], 4);
      //Serial.print(("  "));
      centroid = 0;
    }
    //Serial.println(' ');
  }
  /////////////
  //Impresion de la matriz de etiquetas solo para comprobacion
  //    for (i = 0; i < etiquetas; i++) {
  //      for (j = 0; j < tam_col; j++) {
  //        Serial.print(centroides[i][j]);
  //        Serial.print(' ');
  //      }
  //      Serial.println(' ');
  //    }
  //Encontrar la distancia entre los sensores y la matriz de entrenamiento si clasifica adecuadamente
/* Descripcion del proceso de cnn entre matriz de entrenamiento y centroides */
  //for --filas de la matriz de entrenamiento
  //for --- filas de la matriz de centroides
  //for ---columnas de matriz centroides
  for (i = 0; i < tam_fil; i++) {//se recorre la matriz de entrenamiento 
    for (j = 0; j < etiquetas; j++) { //se recorre la matriz de etiquetas 
      for (l = 0; l < tam_col; l++) {
        promedio = promedio + pow(centroides[j][l] - matriz[i][l], 2);
      }
      distancia = sqrt(promedio);//obtencio de la distancia 
      if (distancia < distancia_menor ) {//calculo de la distancia menor 
        distancia_menor = distancia;
        label = centroides[j][tam_col - 1];
      }
      promedio = 0;
    }
    distancia_menor = 3000;//se vuelve a llenar la variable para futuros calculos 
    if (matriz[i][tam_col - 1] == label) {//se comprueba si se realizo bien 
      //  Serial.print(String(i) + ":");//se imprime d si esta bien 
      // Serial.println("D");
    }
    else {
      //Serial.print(String(i) + ":");//se imprime s si esta mal 
      //Serial.print(i);
      
      int num[s] = {};//vector que guardar las posiciones de s
      //Serial.println("S");
      s++;//aumento de contador 
      num[s-1]=i;//Se llena el vector con las posiciones de donde encuentra s
      float matriz_s[s + etiquetas ][tam_col];//se declara la matriz s
      for (int w = 0; w <=s; w++) {//se recorre en base al numero de s encontrados
        for (int f = 0; f < s + etiquetas; f++) {//recorrido de la matriz 
          for (int c = 0; c < tam_col; c++) {//recorrido de la matriz
            matriz_s[f][c] = centroides[f][c];//se llena con los centroides 
            matriz_s[etiquetas][c] = matriz[num[s-1]][c];//se llena con la fila donde existe s
            //Serial.print(matriz_s[f][c]);//= matriz[i][c]);
            //Serial.print(' ');
          }
          Serial.println(' ');
        }
      }
      //impresion final 
      for (int f = 0; f < s+etiquetas; f++) {
        for (int c = 0; c < tam_col; c++) {
          Serial.print(matriz_s[f][c]);
          Serial.print(' ');
        }
        Serial.println(' ');
      }
    }
  }

  Serial.println(s);

}
