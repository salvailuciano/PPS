/**********************************
PRACTICAS PROFESIONALES SUPERVISADAS (PPS)

Codigo para el firmware del proyecto de actualizacion del sistema de control y volitmetro + pantalla LCD (4x20) de los equipos de RF.

link del repositorio de github: https://github.com/salvailuciano/PPS

MEDICIONES:
1.  PD: potencia transferida
2.  PR: potencia reglejada
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
const float nivelesDigitalesADC = 1023.0;
const float vRefADC = 5;

//Variables auxiliares para calculo de ADC//
const float Iparametro  = 0.1;
//const float Pdparametro  = 1033.05;//(v*v/100)*pdparametro
const float Pdparametro  = 1250;
const float Vexparametro  = 0.1;
const float Agcparametro  = 1;

//Variables a mostrar en pantalla//
float corriente = 0.0;
float potenciad = 0.0;
float vex = 0.0;
float agc = 0.0;

#define inInterrupcion_2 2 // Se define pin 2 para interrupcion
#define inInterrupcion_3 3 // Se define pin 3 para interrupcion

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
  float aux = 0.0;
  float lectura[cantidadMediciones];

//////////////////////LECTURA DE ENTRADA////////////////////////////
// "i=0" Contador importante, por que es el que indica el valor adentro del arreglo
  for(int i=0; i < cantidadMediciones; i++){
    selectChannelMux(i); //Selecciona el canal del multiplexor para tomar la entrada a promediar
    //lectura[i] = readyProm();  //Toma (lee entrada) las MUESTRAS y carga el valor ya promediado en lectura[i]
    lectura[i] = analogRead(i); // Solo para test sin promediador
  }

/////////////////////////////ARREGLO DE LECTURAS/////////////////////////////
// lectura = [     0     ,     1     ,     2     ,     3     ,     4     ] //
// lectura = [ corriente , potenciad ,    vex    ,    agc    ,     X     ] //
/////////////////////////////////////////////////////////////////////////////

// Se podria pasar todo esto de los calculos a una sheet nueva que sea "CalculosADC" o algo por el estilo/////
  Serial.println("calculando");
  corriente = ((lectura[0]*vRefADC)/nivelesDigitalesADC)/Iparametro;
 // corriente = (lectura[0]*5) / 1024;// Solo para test

  //potenciad = ((lectura[1]*vRefADC)/nivelesDigitalesADC)/Pdparametro; // ver este que es distinto
  aux = (lectura[1] * 5.0) / 1024.0;
  aux = (aux*aux)/100;
  potenciad = aux *Pdparametro;
 // potenciad = (lectura[1]*5) / 1024;// Solo para test sin el parametro
 
  vex = ((lectura[2]*vRefADC)/nivelesDigitalesADC)/Vexparametro;
 // vex = (lectura[2]*5) / 1024;// Solo para test sin el parametro
  
  agc = ((lectura[3]*vRefADC)/nivelesDigitalesADC)/Agcparametro;
 // agc = (lectura[3]*5) / 1024; // Solo para test sin el parametro
  
///////////////////////Funciones para el menu y los botones///////////////////////////////////
  leerBotones();
  mostrarValores(corriente,potenciad,vex,agc);
}
/////////////////////////////////////////////////////////TERMINA EL LOOP//////////////////////////////////////////////////////////////
