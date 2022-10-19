#include <Preferences.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
#include <nvs_flash.h>
#include "eeprom.h"
#include "definesConfiguraciones.h"
Preferences preferences;

void readEeprom() {  
  preferences.begin("myproyect", false);
  valorPD = preferences.getFloat("var1",500); //
  valorPR = preferences.getFloat("var2",200); //
  valorAGC = preferences.getFloat("var3",20); //
  valorIsal = preferences.getFloat("var4",8.8); //
  valorVsal = preferences.getFloat("var5",48); //
  valorVexc = preferences.getFloat("var6",28); //
  valorVaux = preferences.getFloat("var7",12); //
  valorVlinea = preferences.getFloat("var8",220); //
  bitsResolucion = preferences.getFloat("var30",12); //

  VARIABLE1=preferences.getString("var10", "P Directa: ");
  VARIABLE2=preferences.getString("var11", "P Refejada: ");
  VARIABLE3=preferences.getString("var12", "AGC: ");
  VARIABLE4=preferences.getString("var13", "I Salida: ");
  VARIABLE5=preferences.getString("var14", "V Salida: ");
  VARIABLE6=preferences.getString("var15", "Vexc: ");
  VARIABLE7=preferences.getString("var16", "V linea: ");
  VARIABLE8=preferences.getString("var17", "Vaux: ");

  UNIDAD1=preferences.getString("var18", "W");
  UNIDAD2=preferences.getString("var19", "W");
  UNIDAD3=preferences.getString("var20", "W");
  UNIDAD4=preferences.getString("var21", "A");
  UNIDAD5=preferences.getString("var22", "V");
  UNIDAD6=preferences.getString("var23", "V");
  UNIDAD7=preferences.getString("var24", "V");
  UNIDAD8=preferences.getString("var25", "V");
  
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
                   preferences.putString("var18", UNIDAD1);
                   break;
           case 1:
                   preferences.putString("var11", VARIABLE2);
                   preferences.putString("var19", UNIDAD2);
                   break;
           case 2:
                   preferences.putString("var12", VARIABLE3);
                   preferences.putString("var20", UNIDAD3);
                   break;
           case 3:
                   preferences.putString("var13", VARIABLE4);
                   preferences.putString("var21", UNIDAD4);
                   break;
           case 4:
                   preferences.putString("var14", VARIABLE5);
                   preferences.putString("var22", UNIDAD5);
                   break;
           case 5:
                   preferences.putString("var15", VARIABLE6);
                   preferences.putString("var23", UNIDAD6);
                   break;
           case 6:
                   preferences.putString("var16", VARIABLE7);
                   preferences.putString("var24", UNIDAD7);
                   break;
           case 7:
                   preferences.putString("var17", VARIABLE8);
                   preferences.putString("var25", UNIDAD8);
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
           case 30:
                   preferences.putFloat("var30", bitsResolucion);
                   break;           
           case 98:
                    nvs_flash_erase(); // erase the NVS partition and...
                    nvs_flash_init(); // initialize the NVS partition.
                    ESP.restart();
                    break;
           case 99:
                   preferences.putFloat("var1", valorPD);
                   preferences.putFloat("var2", valorPR);
                   preferences.putFloat("var3", valorAGC);
                   preferences.putFloat("var4", valorIsal);
                   preferences.putFloat("var5", valorVsal);
                   preferences.putFloat("var6", valorVexc);
                   preferences.putFloat("var7", valorVaux);
                   preferences.putFloat("var8", valorVlinea);
                   preferences.putString("var10", VARIABLE1);
                   preferences.putString("var18", UNIDAD1);
                   preferences.putString("var11", VARIABLE2);
                   preferences.putString("var19", UNIDAD2);
                   preferences.putString("var12", VARIABLE3);
                   preferences.putString("var20", UNIDAD3);
                   preferences.putString("var13", VARIABLE4);
                   preferences.putString("var21", UNIDAD4);
                   preferences.putString("var14", VARIABLE5);
                   preferences.putString("var22", UNIDAD5);
                   preferences.putString("var15", VARIABLE6);
                   preferences.putString("var23", UNIDAD6);
                   preferences.putString("var16", VARIABLE7);
                   preferences.putString("var24", UNIDAD7);
                   preferences.putString("var17", VARIABLE8);
                   preferences.putString("var25", UNIDAD8);
                   preferences.putFloat("var30", bitsResolucion);
                  break;
           default:
                   break;
  }
  preferences.end();
 }
