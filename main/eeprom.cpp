#include <Preferences.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
#include "eeprom.h"
#include "definesConfiguraciones.h"
Preferences preferences;

void readEeprom() {  
  preferences.begin("myproyect", false);
  valorPD = preferences.getFloat("var1", 0); //
  valorPR = preferences.getFloat("var2", 0); //
  valorAGC = preferences.getFloat("var3", 0); //
  valorIsal = preferences.getFloat("var4", 0); //
  valorVsal = preferences.getFloat("var5", 0); //
  valorVexc = preferences.getFloat("var6", 0); //
  valorVaux = preferences.getFloat("var7", 0); //
  valorVlinea = preferences.getFloat("var8", 0); //

  VARIABLE1=preferences.getString("var10", "");
  VARIABLE2=preferences.getString("var11", "");
  VARIABLE3=preferences.getString("var12", "");
  VARIABLE4=preferences.getString("var13", "");
  VARIABLE5=preferences.getString("var14", "");
  VARIABLE6=preferences.getString("var15", "");
  VARIABLE7=preferences.getString("var16", "");
  VARIABLE8=preferences.getString("var17", "");
  
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

void writeEEPROMVariables(short variable){
 
  preferences.begin("myproyect", false);
  switch(variable){


           case 0:
                   preferences.putString("var10", VARIABLE1);
                   break;
           case 1:
                   preferences.putString("var11", VARIABLE2);
                   break;

           case 2:
                   preferences.putString("var12", VARIABLE3);
                   break;
           case 3:
                   preferences.putString("var13", VARIABLE4);
                   break;

           case 4:
                   preferences.putString("var14", VARIABLE5);
                   break;
           case 5:
                   preferences.putString("var15", VARIABLE6);
                   break;

           case 6:
                   preferences.putString("var16", VARIABLE7);
                   break;
           case 7:
                   preferences.putString("var17", VARIABLE8);
                   break;

           case 8:
                   preferences.putFloat("var1", valorPD);
                   break;
           case 9:
                   preferences.putFloat("var2", valorPR);
                   break;

           case 10:
                   preferences.putFloat("var3", valorAGC);
                   break;
           case 11:
                   preferences.putFloat("var4", valorIsal);
                   break;

           case 12:
                   preferences.putFloat("var5", valorVsal);
                   break;
           case 13:
                   preferences.putFloat("var6", valorVexc);
                   break;

           case 14:
                   preferences.putFloat("var7", valorVaux);
                   break;
           case 15:
                   preferences.putFloat("var8", valorVlinea);
                   break;

           default:
                   break;
  }
  preferences.end();
 }
