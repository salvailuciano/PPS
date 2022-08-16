///////////////////////////////////////////////////
/*
 * Una solución más reciente para la interfaz con EEPROM para el ESP32 es utilizar la biblioteca Preferences. La gran diferencia con la librería EEPROM es que en lugar de utilizar direcciones de memoria, utilizamos palabras clave para dirigir las variables. Las palabras clave deben tener como máximo 15 caracteres y deben ser únicas.

Las funciones que hay que conocer son:

putInt (dependiendo del tipo de variable) para escribir la variable en la memoria
getInt( dependiendo del tipo de variable) para leer la variable

*/


#include <Preferences.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences

Preferences preferences;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("Initialize System"));
  int boardId = 18; 
  float param = 26.5;
  
  //init preference
  preferences.begin("myfile", false);
  //preferences.clear(); // remove all preferences in namespace myfile
  //preferences.remove("varname");// remove varname in the namespace


  preferences.putUInt("boardId", boardId);
  preferences.putFloat("param", param);

  unsigned int readId = preferences.getUInt("boardId", 0); // get boardId or if key doesn't exist set variable to 0
  Serial.print("Read Id = ");
  Serial.println(readId);
  
  float readParam = preferences.getFloat("param", 0); //
  Serial.print("Read param = ");
  Serial.println(readParam);
  
  preferences.end();
    
}

void loop() {}
