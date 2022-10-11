#include "adc.h"
#include "menu.h"
#include "promediador.h"
#include "mux.h"
#include "Button.h"
#include "definesConfiguraciones.h"
#include "eeprom.h"
#include "temperatura.h"
#include "serial.h"

//#include <AT24Cxx.h>
const int lineal=0; //si la funcion Tomar medicion recibe un 0 el cálculo será lineal
const int cuadratica=1; //si la funcion Tomar medicion recibe un 1 el cálculo será cuadrático
const float nivelesDigitalesADC = pow(2, bitsResolucion)-1;//1024-1 valores //pow es 2^bits de resolucion
float calAdc=(vSensoresADC*nivelesDigitalesADC)/vRefADC;
float valorPromedio = 0;
float valorPromedio2 = 0;
void tomarMedicion(float valor, float arreglo[], float valor2, float arreglo2[], int medicionN);

//////////////////////// VALORESS DE MEDICION A MOSTRAR EN PANTALLA /////////////////////////////////
float valorPD= 500;
float valorPR= 200;
float valorAGC= 20;
float valorIsal= 8.8;
float valorVsal= 48;
float valorVexc= 28;
float valorVaux= 12;
float valorVlinea= 220; 

String VARIABLE1="P Directa: ";
String VARIABLE2="P Refejada: ";
String VARIABLE3="AGC: ";
String VARIABLE4="I Salida: ";
String VARIABLE5="V Salida: ";
String VARIABLE6="Vexc: ";
String VARIABLE7="Vaux: ";
String VARIABLE8="V linea: ";
String TIPOEQUIPO="M500W";

String UNIDAD1="W";
String UNIDAD2="W";
String UNIDAD3="W";
String UNIDAD4="A";
String UNIDAD5="V";
String UNIDAD6="V";
String UNIDAD7="V";
String UNIDAD8="V";
 
