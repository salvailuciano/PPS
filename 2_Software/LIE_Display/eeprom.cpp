#include <Preferences.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
#include <nvs_flash.h>
#include "eeprom.h"
#include "definesConfiguraciones.h"
Preferences preferences;


//////////////////////////Memoria EEPROM//////////////////////////////////////////
//  En este programa se describe el manejo de la memoria eeprom y el guardado de datos:
/*
La posibilidad de poder guardar datos en la memoria no volatil del microcontrolador
es vital para este proyecto, ya que permite que mediante el protocolo serial
se puedan modificar todos los parametros que se deseen y no se borre la informacion
al cortar el suministro electrico del dispositivo o reiniciarlo.

El microcontrolador esp32, no posee directamente un sistema de memoria EEPROM,
sino una memoria flash, la cual se puede acceder libremente, por lo que se programo
un sistema para reservar una cantidad de memoria fija en la memoria flash
y poder acceder a datos guardados en esta.

Esta memoria flash es una particion llamada NVS partition(non volatile storage),
o en español particion de memoria no volatil 

Lo importante es que el acceso y el nombramiento de variables es individual
y se puede apreciar que en terminos de programacion tiene un funcionamiento simple

Primero se debe creal un nombre al conjunto de variables que se guardara. Esto se asigna
con un nombre x , que contiene el global de las variables.

Luego, se puede guardar todos los tipos de variables existentes apuntando a cada una
con su tipo respectivo. Los tipos de variables mas comun que se pueden guardar son:
-Float
-String
-Int
-Char
-Bool
-Double
-Bytes

Ejemplo

preferences.begin("myproyect", false);
  
valorPD=preferences.getFloat("var1",500);
preferences.putFloat("var1", writeVariable1);

.preferences el namespace standar
.myproyect es el nombre de el espacio donde se guardaran todas las variables
.begin inicializa a la eeprom para leerla o escibirla
.getfloat sera para obtener el valor de la variable guardada y asignarla a valorPD
.putbloat escribe en var1 el valor de la variable writeVariable1 
.var1 es el nombre que se le asigna a la variable en la memoria flash
.500 sera el valor por defecto si no hay nada guardado en ese sector flash

Todo esto ha sido realizado en funciones para evitar repetir programacion y que sea
mas facil manipular las variables.


*/


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
