/**********************************
PRACTICAS PROFESIONALES SUPERVISADAS (PPS)

Codigo para el firmware del proyecto de actualizacion del sistema de control y volitmetro + pantalla LCD (4x20) de los equipos de RF.

link del repositorio de github: https://github.com/salvailuciano/PPS
 **********************************/

#include "menu.h"
#include "promediador.h"
#include "mux.h"
#include "Button.h"

//Variables Utiles//
const int cantidadMediciones = 4;
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



////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(9600);
  Serial.println(F("Initialize System"));

  setup_mux();
  setup_menu();
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
  aux = (lectura[0] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  corriente = aux /Iparametro; // Cálculo para obtener Vin del divisor de tensión
 // corriente = (lectura[0]*5) / 1024;// Solo para test
  
  aux = (lectura[1] * 5.0) / 1024.0;
  aux = (aux*aux)/100;
  potenciad = aux *Pdparametro;
 // potenciad = (lectura[1]*5) / 1024;// Solo para test sin el parametro
  
  aux = (lectura[2] * 5.0) / 1024.0;
  vex = aux /Iparametro;
 // vex = (lectura[2]*5) / 1024;// Solo para test sin el parametro
  
  aux = (lectura[3] * 5.0) / 1024.0;
  agc = aux /Agcparametro;
 // agc = (lectura[3]*5) / 1024; // Solo para test sin el parametro
  
///////////////////////Funciones para el menu y los botones///////////////////////////////////
 //mostrarValores (corriente,potenciad,vex,agc);
 leerBotones();
 
//Muestra valores en pantalla si medicion es distinto de "0" , es decir si no esta en modo configuración
  
  mostrarValores(corriente,potenciad,vex,agc);
  
}
/////////////////////////////////////////////////////////TERMINA EL LOOP//////////////////////////////////////////////////////////////
