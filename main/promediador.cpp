#include "definesConfiguraciones.h"

//Falta agregar un arreglo de valorPromedio[2 o 3], el valorPromedio actual y el anterior, para calcular el nuevo promedio
/*void setup_promediador(){
  float valorPromedio;
}*/
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

/*float calcularProm(float arreglo[]){
  float valorPromedio[2];
  float acumProm=0;
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    acumProm += arreglo[muestraActual];
  }
  valorPromedio = acumProm / cantidadMuestras;
  acumProm  = 0;
  return valorPromedio;//Retorna  el valor  promedio  de la cantidad  de muestras
}*/
