#include "definesConfiguraciones.h"

float calcularProm(float arreglo[]){
  short y=0;
  float valorPromedio;
  float acumProm=0;
  for(int muestraActual = 0 ; muestraActual < Promedio[y] ; muestraActual++){
    acumProm += arreglo[muestraActual];
  }
  valorPromedio = acumProm / Promedio[y];
  acumProm  = 0;
  y++;
  if (y>7) y=0;
  return valorPromedio;//Retorna  el valor  promedio  de la cantidad  de muestras
}
