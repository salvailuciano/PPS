#include <Preferences.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
#include "definesConfiguraciones.h"

Preferences preferences;


void readEeprom(float readParamvalorPD,float readParamvalorPR,float readParamvalorAGC,float readParamvalorIsal,float readParamvalorVsal,float readParamvalorVexc,float readParamvalorVaux,float readParamvalorVlinea) {  
  preferences.begin("myproyect", false);
   readParamvalorPD = preferences.getFloat("var1", 0); //
   readParamvalorPR = preferences.getFloat("var2", 0); //
   readParamvalorAGC = preferences.getFloat("var3", 0); //
   readParamvalorIsal = preferences.getFloat("var4", 0); //
   readParamvalorVsal = preferences.getFloat("var5", 0); //
   readParamvalorVexc = preferences.getFloat("var6", 0); //
   readParamvalorVaux = preferences.getFloat("var7", 0); //
   readParamvalorVlinea = preferences.getFloat("var8", 0); //
  preferences.end();
}

void writeEEPROM(float writeVariable1,float writeVariable2,float writeVariable3, float writeVariable4, float writeVariable5, float writeVariable6, float writeVariable7,float writeVariable8){
   //init preference
 preferences.begin("myproyect", false);
  //preferences.clear(); // remove all preferences in namespace myfile
  //preferences.remove("varname");// remove varname in the namespace
 preferences.putFloat("var1", writeVariable1);
 preferences.putFloat("var2", writeVariable2);
 preferences.putFloat("var3", writeVariable3);
 preferences.putFloat("var4", writeVariable4);
 preferences.putFloat("var5", writeVariable5);
 preferences.putFloat("var6", writeVariable6);
 preferences.putFloat("var7", writeVariable7);
 preferences.putFloat("var8", writeVariable8);
 preferences.end();
  }
