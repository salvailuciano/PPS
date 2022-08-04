/**********************************
PRACTICAS PROFESIONALES SUPERVISADAS (PPS)

Codigo para el firmware del proyecto de actualizacion del sistema de control y volitmetro + pantalla LCD (4x2 0) de los equipos de RF.

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
 **********************************/

#include "menu.h"
#include "promediador.h"
#include "mux.h"
#include "Button.h"
#include "definesConfiguraciones.h"

//Variables auxiliares para calculo de ADC//
const float parametroPD = 0.1;
//const float Pdparametro = 1033.05;//(v*v/100)*pdparametro
const float parametroPR = 0.2;
const float parametroAGC = 0.3;
const float parametroIsal = 0.4;
const float parametroVsal = 0.5;
const float parametroVexc = 0.6;
const float parametroVaux = 0.7;
const float parametroVlinea = 0.8;

float valorPromedio = 0;
float valorPromedio2 = 0;

void tomarMedicion(float parametro, float arreglo[], float parametro2, float arreglo2[], int medicionN);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200);
  Serial.println(F("Initialize System"));

  setup_mux();
  setup_menu();
  //setup_promediador();
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
  Serial.print("##MEDICIONES 1 y 2: ");
  tomarMedicion(parametroPD, potenciaTransferida, parametroPR, potenciaReflejada, 1);
  float potenciaTransferidaProm = valorPromedio;
  float potenciaReflejadaProm = valorPromedio2;
  Serial.print("##MEDICIONES 3 y 4: ");
  tomarMedicion(parametroAGC, AGC, parametroIsal, corrienteSalida, 2);
  float AGCProm = valorPromedio;
  float corrienteSalidaProm = valorPromedio2;
  Serial.print("##MEDICIONES 5 y 6: ");
  tomarMedicion(parametroVsal, tensionSalida, parametroVexc, tensionExc, 3);
  float tensionSalidaProm = valorPromedio;
  float tensionExcProm = valorPromedio2;
  Serial.print("##MEDICIONES 7 y 8: ");
  tomarMedicion(parametroVaux, tensionAux, parametroVlinea, tensionLinea, 0);
  float tensionAuxProm = valorPromedio;
  float tensionLineaProm = valorPromedio2;
  
  //////////////////////ENVIA PROMEDIOS A MENU////////////////////////////
  mostrarValores(potenciaTransferidaProm, potenciaReflejadaProm, AGCProm, corrienteSalidaProm, tensionSalidaProm, tensionExcProm, tensionAuxProm, tensionLineaProm);//Manda los valores promedios a menu //Por ahi hay q hacer el tema de la escala, o enviarlo a la sheet escala (lineal o cuadratica)
  
  Serial.println("Verificacion fuera de la funcion del arreglo");//Verifica que se actualiza el arreglo en el main
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    Serial.print(potenciaTransferida[muestraActual]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("1) PD promedio: ");
  Serial.println(potenciaTransferidaProm);
  Serial.print("2) PR promedio: ");
  Serial.println(potenciaReflejadaProm);
  Serial.print("3) AGC promedio: ");
  Serial.println(AGCProm);
  Serial.print("4) Isal promedio: ");
  Serial.println(corrienteSalidaProm);
  Serial.print("5) Vsal promedio: ");
  Serial.println(tensionSalidaProm);
  Serial.print("6) Vexc promedio: ");
  Serial.println(tensionExcProm);
  Serial.print("7) Vaux promedio: ");
  Serial.println(tensionAuxProm);
  Serial.print("8) Vlinea promedio: ");
  Serial.println(tensionLineaProm);
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
void tomarMedicion(float parametro, float arreglo[], float parametro2, float arreglo2[], int medicionN){
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    arreglo[muestraActual] = ((analogRead(39)*vRefADC)/nivelesDigitalesADC)/parametro;
    arreglo2[muestraActual] = ((analogRead(36)*vRefADC)/nivelesDigitalesADC)/parametro2;
  }


  selectChannelMux(medicionN);//Para dar tiempo al ADC a estabilizar la medicion, mientras calcula el promedio

  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    Serial.print(arreglo[muestraActual]);
    Serial.print(" ");
  }
  Serial.println("");
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
    Serial.print(arreglo2[muestraActual]);
    Serial.print(" ");
  }
  Serial.println();
  leerBotones();
  valorPromedio = calcularProm(arreglo);
  valorPromedio2 = calcularProm(arreglo2);
}
