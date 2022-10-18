#include "definesConfiguraciones.h"

float calcularProm(float arreglo[]){
  float valorPromedio;
  float acumProm=0;
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    acumProm += arreglo[muestraActual];
  }
  valorPromedio = acumProm / cantidadMuestras;
  acumProm  = 0;
  return valorPromedio;//Retorna  el valor  promedio  de la cantidad  de muestras
}
