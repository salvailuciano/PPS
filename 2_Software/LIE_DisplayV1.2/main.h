#include "adc.h"
#include "menu.h"
#include "promediador.h"
#include "mux.h"
#include "Button.h"
#include "definesConfiguraciones.h"
#include "eeprom.h"
#include "temperatura.h"
#include "serial.h"
#include "variablesGlobales.h"
#include "interrupciones.h"

short muxMuestras=0;
short t=0;
const int lineal=0; //si la funcion Tomar medicion recibe un 0 el cálculo será lineal
const int cuadratica=1; //si la funcion Tomar medicion recibe un 1 el cálculo será cuadrático
const float nivelesDigitalesADC = pow(2, bitsResolucion)-1;//1024-1 valores //pow es 2^bits de resolucion
float calAdc=(vSensoresADC*nivelesDigitalesADC)/vRefADC;
float valorPromedio = 0;
float valorPromedio2 = 0;

void tomarMedicion(float valor, float arreglo[], int medicionN,float calibracion1,float tipodeMedicion1);
void tomarMedicion1(float valor2, float arreglo2[], int medicionN, float calibracion2 ,float tipodeMedicion2);
void actualizarPromedios(int valor1, int valor2, int valor3, int valor4, int valor5, int valor6, int valor7, int valor8);
 
