/**********************************
PRACTICAS PROFESIONALES SUPERVISADAS (PPS)

Codigo para el firmware del proyecto de actualizacion del sistema de control y volitmetro + pantalla LCD (4x20) de los equipos de RF.

link del repositorio de github: https://github.com/salvailuciano/PPS

MEDICIONES:
1.  PD: potencia transferida
2.  PR: potencia reflejada
3.  AGC:
4.  I salida: (8,8 A)
5.  V salida: (48 v)
6.  V exc: (28 v)
7.  V aux: fuente interna (12 v)
8.  V línea: (220 v)

INTERRUPCIONES:
noInterrupts(); //desactiva las interrupciones
interrupts(); //vuelve a activar las interrupcione

attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
digitalPinToInterrupt(pin) = pin que se usa para la interrupcion externa
ISR = funcion a la que llama cuando interrumpe (no debe tomar parametros ni devolver)
mode = low, change, falling o rising

detachInterrupt(digitalPinToInterrupt(pin))
desactiva el pin de interrupcion

 **********************************/

#include "menu.h"
#include "promediador.h"
#include "mux.h"
#include "Button.h"
#include "interrupciones.h"

//Variables Utiles//
const int cantidadMediciones = 4;
const int cantidadMuestras = 10;
const float nivelesDigitalesADC = 1023.0;
const float vRefADC = 5;

//Variables auxiliares para calculo de ADC//
const float parametroPD = 1;
//const float Pdparametro = 1033.05;//(v*v/100)*pdparametro
const float parametroPR = 2;
const float parametroAGC = 10;
const float parametroIsal = 100;
const float parametroVsal = 1;
const float parametroVexc = 1;
const float parametroVaux = 1;
const float parametroVlinea = 1;

#define inInterrupcion_2 2 // Se define pin 2 para interrupcion
#define inInterrupcion_3 3 // Se define pin 3 para interrupcion

float tomarMedicion(int medicionN, float parametro, float arreglo[]);
float calcularProm(float arreglo[]);

////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(9600);
  Serial.println(F("Initialize System"));

  setup_mux();
  setup_menu();
  attachInterrupt(digitalPinToInterrupt(inInterrupcion_2), temperatura, RISING);// deja activa la interrupcion 
  attachInterrupt(digitalPinToInterrupt(inInterrupcion_3), roe, RISING);// deja activa la interrupcion 
}

////////////////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
void loop(){
//Se declaran todos los arreglos de cada medicion de 10 muestras cada 1
float potenciaTransferida[cantidadMuestras] {};
float potenciaReflejada[cantidadMuestras] {};
float AGC[cantidadMuestras] {};
float corrienteSalida[cantidadMuestras] {};
float tensionSalida[cantidadMuestras] {};
float tensionExc[cantidadMuestras] {};
float tensionAux[cantidadMuestras] {};
float tensionLinea[cantidadMuestras] {};

//////////////////////LECTURA DE ENTRADA////////////////////////////
  Serial.print("Mediciones 1: ");
  float potenciaTransferidaProm = tomarMedicion(0, parametroPD, potenciaTransferida);
  Serial.print("Mediciones 2: ");
  float potenciaReflejadaProm = tomarMedicion(1, parametroPR, potenciaReflejada);
  Serial.print("Mediciones 3: ");
  float AGCProm = tomarMedicion(2, parametroAGC, AGC);
  Serial.print("Mediciones 4: ");
  float corrienteSalidaProm = tomarMedicion(3, parametroIsal, corrienteSalida);
  float tensionSalidaProm = tomarMedicion(4, parametroVsal, tensionSalida);
  float tensionExcProm = tomarMedicion(5, parametroVexc, tensionExc);
  float tensionAuxProm = tomarMedicion(6, parametroVaux, tensionAux);
  float tensionLineaProm = tomarMedicion(7, parametroVlinea, tensionLinea);
  
  mostrarValores(potenciaTransferidaProm, potenciaReflejadaProm, AGCProm, corrienteSalidaProm);
  
  Serial.print("PD promedio: ");
  Serial.println(potenciaTransferidaProm);
  Serial.print("PR promedio: ");
  Serial.println(potenciaReflejadaProm);
  Serial.print("AGC promedio: ");
  Serial.println(AGCProm);
  Serial.print("Isal promedio: ");
  Serial.println(corrienteSalidaProm);
/*
  for(int medicion = 0; medicion < cantidadMediciones; medicion++){
    selectChannelMux(medicion); //Selecciona el canal del multiplexor para tomar la entrada a medir
      switch(medicion){
        case 0:                           
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                potenciaTransferida[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroPD;
              }
              //for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
              //  Serial.println(F("Initialize System"));
              //}
              //readyProm();
              break; 
        case 1:
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                potenciaReflejada[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroPR;
              }
              //readyProm();
              break;
        case 2:
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                AGC[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroAGC;
              }
              //readyProm();
              break;
        case 3:
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                corrienteSalida[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroIsal;
              }
              //readyProm();
              break;*/
/*      case 4:
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                tensionSalida[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroVsal;
              }
              //readyProm();
              break;
        case 5:
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                tensionExc[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroVexc;
              }
              //readyProm();
              break; 
        case 6:
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                tensionAux[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroVaux;
              }
              //readyProm();
              break;
        case 7:
              for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
                tensionLinea[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametroVlinea;
              }
              //readyProm();
              break; */
//    }  
//potenciad = ((lectura[1]*vRefADC)/nivelesDigitalesADC)/Pdparametro; // ver este que es distinto
//aux = (lectura[1] * 5.0) / 1024.0;
//aux = (aux*aux)/100;
//potenciad = aux *Pdparametro;
//potenciad = (lectura[1]*5) / 1024;// Solo para test sin el parametro
}
/////////////////////////////////////////////////////////TERMINA EL LOOP//////////////////////////////////////////////////////////////


//////////////////////FUNCION tomarMedicion////////////////////////////
float tomarMedicion(int medicionN, float parametro, float arreglo[]){
  selectChannelMux(medicionN);
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    arreglo[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametro;
  }
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    Serial.print(arreglo[muestraActual]);
    Serial.print(" ");
  }
  Serial.println();
  leerBotones();
  return calcularProm(arreglo);
}
//////////////////////FUNCION calcularProm////////////////////////////
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
