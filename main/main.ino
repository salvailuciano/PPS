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

//Tema de potencia, calculo distinto, no recuerdo por que esto//
//potenciad = ((lectura[1]*vRefADC)/nivelesDigitalesADC)/Pdparametro; // ver este que es distinto
//aux = (lectura[1] * 5.0) / 1024.0;
//aux = (aux*aux)/100;
//potenciad = aux *Pdparametro;
//potenciad = (lectura[1]*5) / 1024;// Solo para test sin el parametro

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
#include "definesConfiguraciones.h"

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

float tomarMedicion(float parametro, float arreglo[]);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(9600);
  Serial.println(F("Initialize System"));

  setup_mux();
  setup_menu();
  //setup_promediador();
  attachInterrupt(digitalPinToInterrupt(inInterrupcion_2), temperatura, RISING);// deja activa la interrupcion 
  attachInterrupt(digitalPinToInterrupt(inInterrupcion_3), roe, RISING);// deja activa la interrupcion 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
//Se declaran todos los arreglos de cada medicion de 10 muestras cada 1 y se inicializan en 0 ( {} = cargarlo en 0 )
  float potenciaTransferida[cantidadMuestras] {};
  float potenciaReflejada[cantidadMuestras] {};
  float AGC[cantidadMuestras] {};
  float corrienteSalida[cantidadMuestras] {};
  float tensionSalida[cantidadMuestras] {};
  float tensionExc[cantidadMuestras] {};
  float tensionAux[cantidadMuestras] {};
  float tensionLinea[cantidadMuestras] {};
  
//////////////////////LECTURA DE ENTRADA////////////////////////////
///////////////////////////////////////////////////////////////////
// Funcion "tomarMedicion(float parametro, float arreglo[])": Se le envia el parametro de cada medicion para el calculo del ADC y el arreglo para cargarlo con 10 muestras, retorna promedio de las 10 muestras
/////////////////////////////////////////////////////////////////////
  Serial.print("##MEDICIONES 0: ");
  float potenciaTransferidaProm = tomarMedicion(parametroPD, potenciaTransferida, 1);
  Serial.print("##MEDICIONES 1: ");
  float potenciaReflejadaProm = tomarMedicion(parametroPR, potenciaReflejada, 2);
  Serial.print("##MEDICIONES 2: ");
  float AGCProm = tomarMedicion(parametroAGC, AGC, 3);
  Serial.print("##MEDICIONES 3: ");
  float corrienteSalidaProm = tomarMedicion(parametroIsal, corrienteSalida, 4);
  float tensionSalidaProm = tomarMedicion(parametroVsal, tensionSalida, 5);
  float tensionExcProm = tomarMedicion(parametroVexc, tensionExc, 6);
  float tensionAuxProm = tomarMedicion(parametroVaux, tensionAux, 7);
  float tensionLineaProm = tomarMedicion(parametroVlinea, tensionLinea, 0);

  //////////////////////ENVIA PROMEDIOS A MENU////////////////////////////
  mostrarValores(potenciaTransferidaProm, potenciaReflejadaProm, AGCProm, corrienteSalidaProm);//Manda los valores promedios a menu //Por ahi hay q hacer el tema de la escala, o enviarlo a la sheet escala (lineal o cuadratica)
  
  Serial.println("Verificacion fuera de la funcion del arreglo");//Verifica que se actualiza el arreglo en el main
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    Serial.print(potenciaTransferida[muestraActual]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("PD promedio: ");
  Serial.println(potenciaTransferidaProm);
  Serial.print("PR promedio: ");
  Serial.println(potenciaReflejadaProm);
  Serial.print("AGC promedio: ");
  Serial.println(AGCProm);
  Serial.print("Isal promedio: ");
  Serial.println(corrienteSalidaProm);
}
////////////////////////////////////////////////////////////TERMINA EL LOOP/////////////////////////////////////////////////////////////////

//////////////////////FUNCION tomarMedicion////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1) Esta funcion recibe el canal y llama a selectChannerlMux para empezar a medir
// 2) Itera en cantidadMuestras para completar el arreglo con 10 muestras (hace el analogRead y calcula con los parametros del ADC)
// 3) Luego hace una iteracion mas para imprimir en el serial los arreglos
// 4) Luego llama a la funcion para leerBotones
// 5) Y por ultimo llama a la funcion calcularProm, donde le envia el arreglo de 10 muestras, y retorna en el main el promedio
// IMPORTANTE => LA FUNCION NO RETORNA EL ARREGLO, PERO AL ENVIARLE CADA ARREGLO POR SEPARADO LOS COMPLETA IGUAL, POR LO TANTO ACTUALIZA LOS ARREGLOS EN EL MAIN
// Esto se puede sacar si no es necesario guardar los valores de las muestras, el arreglo se crearía, se completa, se calcula promedio y se borra (sería mas eficaz)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float tomarMedicion(float parametro, float arreglo[], int medicionN){
  
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    arreglo[muestraActual] = ((analogRead(0)*vRefADC)/nivelesDigitalesADC)/parametro;
  }
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    Serial.print(arreglo[muestraActual]);
    Serial.print(" ");
  }
  Serial.println();
  selectChannelMux(medicionN);//Para dar tiempo al ADC a estabilizar la medicion, mientras calcula el promedio
  leerBotones();
  return calcularProm(arreglo);
}
