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

//////////////////////////Calculos del adc///////////////////////////
//  Caso escala lineal:
//  Valor en pantalla = (adcpromedio/calAdc)*valor
//  Donde adcpromedio es el medido 
//  Cal Adc es el valor de adc del sensor a fondo de escala
//  Valor es el valor que se quiere mostrar en pantalla
//
//  Caso escala cuadratica:
//  Valor en pantalla = (adcpromedio/calAdc)^2*valor
//  Donde adcpromedio es el medido 
//  Cal Adc es el valor de adc del sensor a fondo de escala
//  Valor es el valor que se quiere mostrar en pantalla
//
//  Formula propuesta:
//  arreglo[muestraActual] = ((analogRead(muxin_A)*calAdc)*valor;
//  calAdc= (vSensoresADC*nivelesDigitalesADC)/vRefADC
 *******************************************************************/
#include "main.h"

////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200);
  Serial.println(F("inicializando sistema"));
  setup_adc();
  setup_mux();
  setup_menu();
  setup_temperatura();
  setup_interrupcion();
  readEeprom();// Lee los valores almacenados en la eeprom
}
////////////////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
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
  //Serial.print("##MEDICIONES 1 y 2: ");
  tomarMedicion(valorPD, potenciaTransferida, valorPR, potenciaReflejada, 1, cuadratica, cuadratica);
  float potenciaTransferidaProm = valorPromedio;
  float potenciaReflejadaProm = valorPromedio2;
  //Serial.print("##MEDICIONES 3 y 4: ");
  tomarMedicion(valorAGC, AGC, valorIsal, corrienteSalida, 2, lineal, lineal);
  float AGCProm = valorPromedio;
  float corrienteSalidaProm = valorPromedio2;
  //Serial.print("##MEDICIONES 5 y 6: ");
  tomarMedicion(valorVsal, tensionSalida, valorVexc, tensionExc, 3, lineal, lineal);
  float tensionSalidaProm = valorPromedio;
  float tensionExcProm = valorPromedio2;
  //erial.print("##MEDICIONES 7 y 8: ");
  tomarMedicion(valorVaux, tensionAux, valorVlinea, tensionLinea, 0, lineal, lineal);
  float tensionAuxProm = valorPromedio;
  float tensionLineaProm = valorPromedio2;
  float temperatura=lecturaTemperatura();
  
  mostrarTemperatura(temperatura);
  mostrarCalibraciones();
  mostrarcalibracionSerial();
  mostrarnombreVariables();
  
  //////////////////////ENVIA PROMEDIOS A MENU////////////////////////////
  if (interruptCounter > 0) {
 
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
 
  mostrarValores(potenciaTransferidaProm, potenciaReflejadaProm, AGCProm, corrienteSalidaProm, tensionSalidaProm, tensionExcProm, tensionAuxProm, tensionLineaProm);//Manda los valores promedios a menu 
  Serial.println("Midiendo");
  }
  if(flagValores==true){
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
    flagADC=false;
    flagValores=false;
  }
}

////////////////////////////////////////////////////////////TERMINA EL LOOP/////////////////////////////////////////////////////////////////

//////////////////////FUNCION tomarMedicion////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1) Esta funcion recibe el canal y llama a selectChannerlMux para empezar a medir
// 2) Itera en cantidadMuestras para completar el arreglo con 10 muestras (hace el analogRead y calcula con los parametros del ADC)
// 3) Luego hace una iteracion mas para imprimir en el serial los arreglos
// 4) Luego llama a la funcion para leerBotones
// 5) Y por ultimo llama a la funcion calcularProm, donde le envia el arreglo de 10 muestras, y retorna en el main el promedio
// 6) Incluye el tipo de medicion para determinar el cálculo dependiendo si es lineal o cuadrática.
// 7) En esta misma funcion se pueden medir dos tipos de medicion diferentes sin que afecten una a la otra
// IMPORTANTE => LA FUNCION NO RETORNA EL ARREGLO, PERO AL ENVIARLE CADA ARREGLO POR SEPARADO LOS COMPLETA IGUAL, POR LO TANTO ACTUALIZA LOS ARREGLOS EN EL MAIN
// Esto se puede sacar si no es necesario guardar los valores de las muestras, el arreglo se crearía, se completa, se calcula promedio y se borra (sería mas eficaz)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tomarMedicion(float valor, float arreglo[], float valor2, float arreglo2[], int medicionN,int tipodeMedicion1,int tipodeMedicion2){
  
  for(int muestraActual = 0 ; muestraActual < cantidadMuestras ; muestraActual++){
int aux1,aux2=0;
  if (tipodeMedicion1==0){
    arreglo[muestraActual] = (analogRead(muxin_A)/calAdc)*valor; // El arreglo toma el valor de la primera medicion en escala lineal
    }
    else{
    arreglo[muestraActual] = sq((analogRead(muxin_A)/calAdc))*valor;//sq es la lectura al cuadrado// El arreglo toma el valor de la primera medicion en escala cuadratica
     }
     delayMicroseconds(30);
  
  if (tipodeMedicion2==0){
  //  arreglo2[muestraActual] = (analogRead(muxin_B)/calAdc)*valor2; // El arreglo toma el valor de la primera medicion en escala lineal
        
      aux1 = analogRead(muxin_B); // El arreglo toma el valor de la primera medicion en escala lineal
      arreglo2[muestraActual] =   map(aux1, 0, nivelesDigitalesADC, 0, valor2);
    }
    else{
    arreglo2[muestraActual] = sq((analogRead(muxin_B)/calAdc))*valor2;// El arreglo toma el valor de la primera medicion en escala cuadratica
     }
  }
     delayMicroseconds(30);
  selectChannelMux(medicionN);//Para dar tiempo al ADC a estabilizar la medicion, mientras calcula el promedio
 
  if(flagADC==true){
    Serial.println();
    muxMuestras++;
    Serial.print(muxMuestras);
    Serial.print(") Valor ADC");
    Serial.print(muxMuestras);
    Serial.print(" : ");
    Serial.print(analogRead(muxin_A));
  
    Serial.println();
    muxMuestras++;
    Serial.print(muxMuestras);
    Serial.print(") Valor ADC");
    Serial.print(muxMuestras);
    Serial.print(" : ");
    Serial.print(analogRead(muxin_B));
 
    if (muxMuestras>7) muxMuestras=0;
  }
 
 
  leerBotones();
  valorPromedio = calcularProm(arreglo);
  valorPromedio2 = calcularProm(arreglo2);
 
}
