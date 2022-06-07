/**********************************
PRACTICAS PROFESIONALES SUPERVISADAS (PPS)

Codigo para el firmware del proyecto de actualizacion del sistema de control y volitmetro + pantalla LCD (4x20) de los equipos de RF.

link del repositorio de github: https://github.com/salvailuciano/PPS
 **********************************/

#include "menu.h"
#include "promediador.h"
#include "mux.h"

const float Iparametro  = 0.1;
//const float Pdparametro  = 1033.05;//(v*v/100)*pdparametro
const float Pdparametro  = 1250;
const float Vexparametro  = 0.1;
const float Agcparametro  = 1;
const int numReadings = 10; 

int pagina=1;

float corriente = 0.0; //Definimos la variable Vin
float potenciad = 0.0; //Definimos la variable Vin
float vex = 0.0; //Definimos la variable Vin
float agc = 0.0; //Definimos la variable Vin


////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////
void setup() 
{

  Serial.begin(9600);// Inicializa el serial
  Serial.println(F("Initialize System"));

  setup_mux(); //Inicializa el multiplexor
  setup_menu(); //Inicializa el menu

}
////////////////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
void loop() 
{

  float aux = 0.0; //Definimos la variable auxiliar
  int i=0; //Contador
  float lectura[3]  ;//Definimos la variable lectura
  
//////////////////////LECTURA DE ENTRADA////////////////////////////
  for(i=0;i<4;i++)
  {
    selectChannelMux(i); //Selecciona el canal del multiplexor para tomar la entrada a promediar
    lectura[i] = readyprom();  //Carga el valor ya promediado en lectura[i]
  }
  
/////////////////////////////ARREGLO DE LECTURAS///////////////////////////
// lectura = [     0     ,     1     ,     2     ,     3     ,     4     ]
// lectura = [ corriente , potenciad ,    vex    ,    agc    ,     X     ]
//

// Se podria pasar todo esto de los calculos a una sheet nueva que sea "CalculosADC" o algo por el estilo/////

  Serial.println("calculando");
  aux = (lectura[0] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  corriente = aux /Iparametro; // Cálculo para obtener Vin del divisor de tensión
  corriente = (lectura[0]*5) / 1024;
  
  aux = (lectura[1] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  aux = (aux*aux)/100;
  potenciad = aux *Pdparametro; // Cálculo para obtener Vin del divisor de tensión
  potenciad = (lectura[1]*5) / 1024;
  
  aux = (lectura[2] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  vex = aux /Iparametro; // Cálculo para obtener Vin del divisor de tensión
  vex = (lectura[2]*5) / 1024;
  
  aux = (lectura[3] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  agc = aux /Agcparametro; // Cálculo para obtener Vin del divisor de tensión
  agc = (lectura[3]*5) / 1024;
  
  ///////////////////////Funciones para el menu y el encoder///////////////////////////////////
  selectOption();
  encoder(pagina);

  //Muestra valores en pantalla si pagina es distinto de "0"
  if(pagina!=0)
  {
    mostrarValores(corriente,potenciad,vex,agc);
  }
}
