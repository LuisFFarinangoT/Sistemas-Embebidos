/*UTN -FICA -CIERCOM 
 * SISTEMAS EMBEBIDOS 
 * ALGORITMO KNN_N VECINOS 
 * 
*/
#include"matrizentrenamiento.h";//Incluir la matriz de trabajo 
//#define col 5
//#define fil 120
float datosprueba[5] = {6.1 , 2.9 , 4.7, 1.4, 2};//datos de prueba 
float etiq;//variable para guardar la etiqueta 
int respuesta;//variable que guardara la respuesta del programa 
void setup() {
  Serial.begin(9600);//inicio de comunicacion serial 
}
//*************************************************************************************************************
void loop() {
  respuesta = knn(3, 3, 120, 5);//Se llama al método 
  Serial.print(respuesta);//se imprime el resultado del método 
  switch (respuesta)//Opciones posibles que devolverá el método 
  {case 1://para el caso de la primera flor 
  Serial.println("El parametro corresponde a Iris-setosa");//impresión de resultados 
  break ;
  case 2://para el caso de la primera flor
  Serial.println("El parametro corresponde a Iris-versicolor");//impresión de resultados 
  break;
  case 3 ://para el caso de la primera flor
  Serial.println("El parametro corresponde a Iris-virginica");//impresión de resultados 
  break;
    }
  delay(5000);//retardo entre procesos 
}
//*************************************************************************************************************


int knn(int k, int etiquetas, int tam_fil, int tam_col) {//metodo que realiza el algoritmo 
  int col;//variable para las columnas de la matriz 
  int fil;//variable para las filas de la matriz 
  int i = 0;//variable para conteo en ciclos for 
  int j = 0;//variable para conteo en ciclos for 
  float aux;//variable para ordenamiento de matriz 
  float aux_etiq;//variable para ordenamiento de matriz
  float resul=0;//variable donde se guardará el resultado del método 
  float sum = 0; //sumatoria de la elevacion al cuadrado de cada columna
  float distancia = 0; //raiz de sumatoria
  float numr=0;
  float matriz_k[3][k];//matriz que guardará los datos de vecinos 
  int matriz_etiq[2][etiquetas];//matriz que guardará los datos de las etiquetas 
  
  for (i = 0; i < k; i++) { //inicializacion de los dos vectores en cero
    matriz_k[0][i] = i + 1; //se añade las etiquetas de los vecinos
    matriz_k[1][i] = 0;//
    matriz_k[2][i] = 3000 + i; //suma sera de cero
  }
  for (i = 0; i < etiquetas; i++) {
    matriz_etiq[0][i] = i + 1; //se añade las etiquetas de la base de datos en la primera fila de la matriz
    matriz_etiq[1][i] = 0;//suma sera de cero
  }
 //Desarrollo del Algoritmo 
  /*
     1.Leer cada de la matriz de entrenamiento
     2.Distancia entre la fila de la matriz y el vector de prueba (nueva instancia )
     3.Ordenar la matriz matriz_k(determinar los k vecinos de menor distancia )
     4.Contar las etiquetas en la matriz_K y asignar en la matriz etiquetas
     5.Eleccion de mayor numero de matriz_etiq
     6.Retorno de etiqueta resultante
  */
  for (fil = 0; fil < tam_fil; fil++) {//lectura de la matriz 
    for (col = 0; col < tam_col - 1; col++) {//lectura de la matriz 
      sum = sum + pow(matriz[fil][col] - datosprueba[col], 2); //promedio entre operacion del vector de prueba y matriz
    }
    distancia = sqrt(sum); //calculo de la distancia entre el vector de prueba y la matriz de entrenamiento
    //ordenamiento de los datos la matriz 
    if (distancia > 0 && distancia < matriz_k[2][k - 1]) //compracion de nuevo dato con solo la ditancia mayor almacenada en matriz k
    //se analiza con distancia >0 para evitar situaciones donde se llena un campo de la matriz con 0
    { matriz_k[2][k - 1] = distancia;//Asignacion de campos de matriz 
      matriz_k[1][k - 1] = matriz[fil][tam_col - 1 ]; //si se coloca menos 1 la matriz vacia la ultima poisicion
      for (i = 0; i < k; i++) {//recorrido de la matriz en filas y columnas 
        for (j = i + 1; j < k ; j++) {//recorrido de la matriz en filas y columnas
          if (matriz_k[2][i] > matriz_k[2][j] )//condicion de ordenamiento 
          { 
            aux = matriz_k[2][i];//uso de auxliar para ordenamiento 
            matriz_k[2][i] = matriz_k[2][j];
            matriz_k[2][j] = aux;//etiqueta
            aux_etiq = matriz_k[1][i];//uso de auxliar para ordenamiento
            matriz_k[1][i] = matriz_k[1][j];
            matriz_k[1][j] = aux_etiq;
          }//final if
        }//final for
      }//final ordenamiento
    }//fin de la condicion de lectura y ordenamiento 
    sum = 0;
  }//fin de lectura de matriz
//  for (int i = 0; i < k; i++) {//impresion de matriz k
//    Serial.print(matriz_k[0][i]);
//    Serial.print('-');
//    Serial.print(matriz_k[1][i]);
//    Serial.print('-');
//    Serial.println(matriz_k[2][i]);
//  }
  for (i = 0; i < etiquetas; i++) {//Asignacion de las etiquetas para la matriz_etiq
    matriz_etiq[1][i] = matriz_k[1][i];
  }
//  for (i = 0 ; i < etiquetas; i++) {//Impresion de la matriz de etiquetas 
//    Serial.print(matriz_etiq[0][i]);
//    Serial.print('-');
//    Serial.println(matriz_etiq[1][i]);
//  }

  for (i = 0 ; i < etiquetas; i++) {//Obtencion de la etiqueta resultante 
    if (matriz_etiq[1][i]>resul)//se busca el numero que se repite 
      resul=matriz_etiq[1][i];//se reemplaza dicho numero en resultado 
      
      
  }
  return resul;//el método devuelve el numero repetido que será la etiqueta 
  //contar por columna cuantos vecinos hay por etiqueta


}
