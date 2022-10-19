#include <Arduino.h>
//////////////////////////////////// FUSES ////////////////////////////////////////////
//#define DEBUG_VALORES // Se debugean valores por serial si se utiliza esta funcion

/////////////////////////////DECLARACION DE PINES//////////////////////////////////////
//PINES DE BOTONES
//#define Bot_left   12
//#define Bot_right  11
#define Bot_up     5
#define Bot_down   0
#define Bot_enter  15
//PINES DE MUX
#define channelA 27
#define channelB 14
#define muxin_A 36
#define muxin_B 39
//PIN DE SENSOR DE TEMPERATURA
#define DHTPIN 23    // Pin donde está conectado el sensor

///////////////////////// CONFIGURACION MEDICIONES Y ADC///////////////////////////////
const int cantidadMediciones = 8;//
const int cantidadMuestras = 16;
const float vRefADC = 2.2;// si se usa la atenuacion de 6.6db es decir el valor maximo de 4095 se dara a 2.2v
const float vSensoresADC = 2; //tension de los sensores en la medicion buscada establecida en 2v a fullscale

//////////////////////////DEFINIR NOMBRE DE VARIABLES/////////////////////////////////
extern String VARIABLE1;
extern String VARIABLE2;
extern String VARIABLE3;
extern String VARIABLE4;
extern String VARIABLE5;
extern String VARIABLE6;
extern String VARIABLE7;
extern String VARIABLE8;
extern String TIPOEQUIPO;

//////////////////////////DEFINIR UNIDADES DE VARIABLES////////////////////////////////
extern String UNIDAD1;
extern String UNIDAD2;
extern String UNIDAD3;
extern String UNIDAD4;
extern String UNIDAD5;
extern String UNIDAD6;
extern String UNIDAD7;
extern String UNIDAD8;

//////////////////////////DEFINIR NOMBRE DE VARIABLES A MEDIR///////////////////////////////
extern float valorPD;
extern float valorPR;
extern float valorAGC;
extern float valorIsal;
extern float valorVsal;
extern float valorVexc;
extern float valorVaux;
extern float valorVlinea;
