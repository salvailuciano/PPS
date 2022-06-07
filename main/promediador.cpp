#include <Arduino.h>
#include "mux.h"//Para mi esta libreria no la usa
#define MUESTRAS 10 //Cantidad de muestras a promediar

///////////////////////////////PROMEDIADOR/////////////////////////////////////
//El canal ya fue seleccionado en selectChannelMux(i);, entonces por ese canal se toman las muestras a promediar

float readyprom()
{
  float valorPromedio;
  float acumprom=0;   //acumulador
  int j=0;  //contador
  
  for(j=0;j<MUESTRAS;j++)
  {
    valorPromedio = analogRead(0); //Leemos el pin analógico Ai  
    acumprom+= valorPromedio ; //Se acumulan los valores de la cantidad de muestras
  }
    valorPromedio = acumprom / MUESTRAS; //Se calcula el promedio
    acumprom = 0;
    return valorPromedio; //Retorna el valor promedio de la cantidad de muestras
}

  
