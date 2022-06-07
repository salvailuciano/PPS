/**********************************
 *  LaBuhardillaDelLoco.xyz
 *  http://bit.ly/2MTrGne
 *  
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
void setup() {

Serial.begin(9600);
Serial.println(F("Initialize System"));



setup_mux();
setup_menu();

}
////////////////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
void loop() {

  float aux = 0.0; //Definimos la variable auxiliar
  int i=0;
  float lectura[3]  ;//Definimos la variable value

   for(i=0;i<4;i++)
  {
       lectura[i]= readyprom(i);
  
  }
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
  
  selectOption();
  encoder(pagina);
  if(pagina!=0)mostrarValores(corriente,potenciad,vex,agc);
  
}
