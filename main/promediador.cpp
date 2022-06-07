#include <Arduino.h>
#include "mux.h"//Para mi esta libreria no la usa
#define MUESTRAS 10 //Cantidad de muestras a promediar

///////////////////////////////PROMEDIADOR Y LEE ENTRADAS/////////////////////////////////////
//El canal ya fue seleccionado en selectChannelMux(i);, entonces por ese canal se toman las muestras a promediar

float readyProm(){
  float valorPromedio;
  float acumProm=0;
  int j=0;
  
  for(j=0;j<MUESTRAS;j++){
    valorPromedio = analogRead(0); //Leemos el pin analógico Ai
    acumProm += valorPromedio ;
  }
  valorPromedio = acumProm / MUESTRAS;
  acumProm = 0;
  return valorPromedio; //Retorna el valor promedio de la cantidad de muestras
}

  
