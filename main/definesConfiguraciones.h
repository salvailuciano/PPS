#include <Arduino.h>
//////////////////////////DEFINIR NOMBRE DE VARIABLES//////////////////////////////////
#define VARIABLE1                         "P Directa: "
#define VARIABLE2                         "P Refejada: "
#define VARIABLE3                         "AGC: "
#define VARIABLE4                         "I Salida: "
#define VARIABLE5                         "V Salida: "
#define VARIABLE6                         "Vexc: "
#define VARIABLE7                         "Vaux: "
#define VARIABLE8                         "V linea: "
#define POTENCIA500W
#define NUMERO EQUIPO                     "M500W"

//////////////////////////DEFINIR UNIDADES DE VARIABLES//////////////////////////////////
#define UNIDAD1                         "W"
#define UNIDAD2                         "W"
#define UNIDAD3                         "W"
#define UNIDAD4                         "A"
#define UNIDAD5                         "V"
#define UNIDAD6                         "V"
#define UNIDAD7                         "V"
#define UNIDAD8                         "V"
///////////////////////// CONFIGURACION MEDICIONES Y ADC////////////////////////////////
const int bitsResolucion = 12;
const int cantidadMediciones = 8;
const int cantidadMuestras = 16;
const float nivelesDigitalesADC = 4095;
const float vRefADC = 3.3;


//////////////////////// PARAMETROS DE MEDICION /////////////////////////////////

//const float Pdparametro = 1033.05;//(v*v/100)*pdparametro
#define parametroPD 1
#define parametroPR 1
#define parametroAGC 1
#define parametroIsal 1
#define parametroVsal 1
#define parametroVexc 1
#define parametroVaux 1
#define parametroVlinea 1 

///////////////////////////DECLARACION DE PINES//////////////////////////////////

/////////////////////////DECLARACION DE ADC REF////////////////////////////

#define Bot_enter  15

/////////////////////////DECLARACION DE PINES BOTONES////////////////////////////
//#define Bot_left   12
//#define Bot_right  11
#define Bot_up     5
#define Bot_down   0
#define Bot_enter  15

////////////////////////DECLARACION DE PINES MUX/////////////////////////////////
#define channelA 27
#define channelB 14

#define muxin_A 36
#define muxin_B 39
///////////////////////////////////////////////////////////////////////////////
