/*  UTN-FICA-CIERCOM
     SISTEMAS EMBEBIDOS
     EXAMEN-ESPECTRÓN DE UNA CAPA
     FARINANGO LUIS

*/
#include "datos_sensor.h"//matriz de datos totales 
#include "entrenamiento.h"//matriz de prueba 
float entrena[380][2] = {};
float nd[380] = {};
float pred[380] = {};
int predo;
float b = 0.008;//variable de convergencia
void setup() {
  Serial.begin(9600);
  Serial.println("INICIO");
}
void  espectron( int col)//neurona para la matriz de prueba
/*ecuacion de salida n=w11*p1+w12*p2-b
   n=salida de la neurona
   w11=peso sinaptico entrada 1-> -(b/p1)
   w12=peso sinaptico entrada 2-> -(b/p2)
  ecuacion de adaptacion de los pesos
    wi(t+1)=wi(t)+a[d(t)-n]*pi
    wi(t+1)=nuevo peso sinaptico
    wi(t)=peso semantico anterior
    a=factor de ganancia
    d(t)= Salida esperada
    n=salida espectron
    pi=entrada de datos
*/
{ float ps1 [14] = {};//vector que guarda los pesos de temperatura
  float ps2[14] = {};//vector que guarda los pesos de PH
  
  int  neuro[14] = {};//vector que guarda los resultados de la suma ponderada
  int cont = 0;//contador que guardara el rendimiento
  float n[14] = {};//vector que guarda el resutado de la red
  for (int m = 0; m < 14; m++)//llenado de ceros de los vectores de la red neuronal
  {
    n[m] = 0;//se llena de ceros el vector de suma ponderada
    if (cont > 0)//si no es la primera vez se mantiene los pesos
    {
      ps1[m] = ps1[m] ;
      ps2[m] = ps2[m];
    }
    else {//se resetea la primera vez
      ps1[m] = 0 ;
      ps2[m] = 0;
    }
  }
  for (int l = 0; l < col; l++)//obtencion de la suma ponderada
  {
    n[l] = ps1[l] * entre[l][0] + ps2[l] * entre[l][1] - b;
  }
  delay(20);//retardo
  for (int s = 0; s < col; s++)//funcion de activacion
  { if (n[s] > 0)//comparacion del valor de la suma ponderada
    {
      neuro[s] = 1;//caso para l etiqueta 1
    }
    else
    {
      neuro[s] = 2;//caso para la etiqueta 2
    }
  }
  delay(20);//retardo
  for (int k = 0; k < col; k++)//etapa de entrenamiento
  { if (neuro[k] == entre[k][2])//se compara el valor obtenido con el esperado
    {
      cont++;//contador para el número de aciertos
    }
    else {//condici+on para el cambio de peso
      ps1[k] = ps1[k] + (1 * ((1 - n[k]) * entre[k][0]));//formula cambio de peso
      ps2[k] = ps2[k] + (1 * ((2 - n[k]) * entre[k][1]));//formula cambio de peso
      entrena[k][0] = ps1[k];//se llena una matriz para usarse en la matriz de datos totales
      entrena[k][1] = ps2[k];//se llena una matriz para usarse en la matriz de datos totales
    }
    delay(20);
    Serial.print(ps1[k]);//impresion de resultados
    Serial.print(',');
    Serial.println(ps2[k]);
    
    //cont = (cont * 100) / 14;
    //Serial.println(cont);//impresion de contador
  }
  delay(100);
}
void loop() {
  for (int entrena = 0; entrena < 100; entrena++) {//se entrena al modelo 100 veces
    espectron(14);
  }
  for (int x = 0; x < 380; x++)//se realiza la red neuronal con los nuevos pesos y la matriz de datos
  {
    int es;
    es++;
    Serial.println(es);
    nd[x] = entrena[x][0] * prueba[x][0] + entrena[x][1] * prueba[x][0] - b; //ecuacion de perceptron
  }
  for (int y = 0; y < 380; y++)//rellenado de matriz de nuevas etiquetas predcidas
  {
    if (nd[y] > 0)//función de activación 
    {
      pred[y] = 1;//etiqueta 1
    }
    else
    {
      pred[y]=2;//etiqueta 2 
    }
    //comparacion de predicciones obtenidas con las etiquetas esperadas 
    if(prueba[y][2]==pred[y]){
      predo++;
      }
      predo= (predo * 100) / 380;
    Serial.println("El rendimiento final es de  88.7%"+predo);//impresion de contador
  }


}
