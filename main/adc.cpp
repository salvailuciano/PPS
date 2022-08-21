  //////////////////////// Conversor analogico bits ////////////////////////////////////
#include <Arduino.h>
#include "definesConfiguraciones.h"

void setup_adc(){
  
  analogReadResolution(bitsResolucion); //se puede setear de 9 a 12 bits
//  analogSetCycles(8);// steea numero de ciclos por muestra por rango que va de 1 a 255 default 8

  /*
  * Setea la atenuacion para todos los canales
  * Por defecto es 11db
  * */
  analogSetAttenuation(ADC_11db); //ADC_0db, ADC_2_5db, ADC_6db, ADC_11db

  /*
  * Setea la atenuacion para todos los canales
  * Por defecto es 11db
  * 
  *analogSetPinAttenuation(pin, ADC_11db); //ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
  */
 
  /*
   * Cuando VDD_A es 3.3V:
   *
   * - 0dB attenuaton (ADC_ATTEN_DB_0) da full escala de voltaje a 1.1V
   * - 2.5dB attenuation (ADC_ATTEN_DB_2_5) da full escala de voltaje a 1.5V
   * - 6dB attenuation (ADC_ATTEN_DB_6) da full escala de voltaje a 2.2V
   * - 11dB attenuation (ADC_ATTEN_DB_11) da full escala de voltaje a 3.9V, en este caos 3.3V que es el vdd
  */
  
  }
