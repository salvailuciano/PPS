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
//1024 valores
const int bitsResolucion=10;
const int cantidadMediciones = 8;//
const int cantidadMuestras = 16;
const float vRefADC = 2.2;// si se usa la atenuacion de 6.6db es decir el valor maximo de 4095 se dara a 2.2v
const float vSensoresADC = 2; //tension de los sensores en la medicion buscada establecida en 2v a fullscale



//////////////////////////////////// FUSES /////////////////////////////////////////////
//#define DEBUG_VALORES // Se debugean valores por serial si se utiliza esta funcion

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////DECLARACION DE PINES//////////////////////////////////

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
////////////////DECLARACION DE PINES SENSOR TEMPERATURA/////////////////////////
#define DHTPIN 23    // Pin donde está conectado el sensor
