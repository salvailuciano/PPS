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
  
  VARIABLE1=preferences.getString("var10", "PD_ANTE:");
  VARIABLE2=preferences.getString("var11", "PR_ANTE:");
  VARIABLE3=preferences.getString("var12", "%_AUDIO:");
  VARIABLE4=preferences.getString("var13", "I_SAL:");
  VARIABLE5=preferences.getString("var14", "V_SAL:");
  VARIABLE6=preferences.getString("var15", "V_EXC:");
  VARIABLE7=preferences.getString("var16", "V_AUX:");
  VARIABLE8=preferences.getString("var17", "V_LINEA:");
  
  UNIDAD1=preferences.getString("var18", "Wav");
  UNIDAD2=preferences.getString("var19", "Wav");
  UNIDAD3=preferences.getString("var20", "%");
  UNIDAD4=preferences.getString("var21", "A");
  UNIDAD5=preferences.getString("var22", "Vcc");
  UNIDAD6=preferences.getString("var23", "Vcc");
  UNIDAD7=preferences.getString("var24", "Vcc");
  UNIDAD8=preferences.getString("var25", "Vca");

  Escala1 = preferences.getFloat("var26",1); //
  Escala2 = preferences.getFloat("var27",1); //
  Escala3 = preferences.getFloat("var28",0); //
  Escala4 = preferences.getFloat("var29",0); //
  Escala5 = preferences.getFloat("var30",0); //
  Escala6 = preferences.getFloat("var31",0); //
  Escala7 = preferences.getFloat("var32",0); //
  Escala8 = preferences.getFloat("var33",0); //

  Promedio[0] = preferences.getFloat("var34",4); //
  Promedio[1] = preferences.getFloat("var35",8); //
  Promedio[2] = preferences.getFloat("var36",16); //
  Promedio[3] = preferences.getFloat("var37",8); //
  Promedio[4] = preferences.getFloat("var38",4); //
  Promedio[5] = preferences.getFloat("var39",8); //
  Promedio[6] = preferences.getFloat("var40",4); //
  Promedio[7] = preferences.getFloat("var41",8); //

  CalADC1 = preferences.getFloat("var42",1023); //
  CalADC2 = preferences.getFloat("var43",1023); //
  CalADC3 = preferences.getFloat("var44",1023); //
  CalADC4 = preferences.getFloat("var45",1023); //
  CalADC5 = preferences.getFloat("var46",1023); //
  CalADC6 = preferences.getFloat("var47",1023); //
  CalADC7 = preferences.getFloat("var48",1023); //
  CalADC8 = preferences.getFloat("var49",1023); //

  bitsResolucion = preferences.getFloat("var50",10); //

  TIPOEQUIPO = preferences.getString("var51","TFM1000");
  
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

void writeEEPROMCal(float writeVariable1,float writeVariable2,float writeVariable3, float writeVariable4, float writeVariable5, float writeVariable6, float writeVariable7,float writeVariable8){
   //init preference
  preferences.begin("myproyect", false);
  //preferences.clear(); // remove all preferences in namespace myfile
  //preferences.remove("varname");// remove varname in the namespace
  preferences.putFloat("var42", CalADC1);
  preferences.putFloat("var43", CalADC2);
  preferences.putFloat("var44", CalADC3);
  preferences.putFloat("var45", CalADC4);
  preferences.putFloat("var46", CalADC5);
  preferences.putFloat("var47", CalADC6);
  preferences.putFloat("var48", CalADC7);
  preferences.putFloat("var49", CalADC8);

  preferences.end();
 }


void writeEEPROMVariables(short variable){

  preferences.begin("myproyect", false);
  switch(variable){
           case 0:
                   preferences.putFloat("var1", valorPD);
                   preferences.putString("var10", VARIABLE1);
                   preferences.putString("var18", UNIDAD1);
                   preferences.putFloat("var26", Escala1);    
                   preferences.putFloat("var34", Promedio[0]);   
                   break;
           case 1:
                   preferences.putFloat("var2", valorPR);
                   preferences.putString("var11", VARIABLE2);
                   preferences.putString("var19", UNIDAD2);
                   preferences.putFloat("var27", Escala2);
                   preferences.putFloat("var35", Promedio[1]);  
                   break;
           case 2:
                   preferences.putFloat("var3", valorAGC);
                   preferences.putString("var12", VARIABLE3);
                   preferences.putString("var20", UNIDAD3);
                   preferences.putFloat("var28", Escala3);
                   preferences.putFloat("var36", Promedio[2]);  
                   break;
           case 3:
                   preferences.putFloat("var4", valorIsal);
                   preferences.putString("var13", VARIABLE4);
                   preferences.putString("var21", UNIDAD4);
                   preferences.putFloat("var29", Escala4);
                   preferences.putFloat("var37", Promedio[3]);  
                   break;
           case 4:
                   preferences.putFloat("var5", valorVsal);
                   preferences.putString("var14", VARIABLE5);
                   preferences.putString("var22", UNIDAD5);
                   preferences.putFloat("var30", Escala5);
                   preferences.putFloat("var38", Promedio[4]);  
                   break;
           case 5:
                   preferences.putFloat("var6", valorVexc);
                   preferences.putString("var15", VARIABLE6);
                   preferences.putString("var23", UNIDAD6);
                   preferences.putFloat("var31", Escala6);
                   preferences.putFloat("var39", Promedio[5]);  
                   break;
           case 6:
                   preferences.putFloat("var7", valorVaux);
                   preferences.putString("var16", VARIABLE7);
                   preferences.putString("var24", UNIDAD7);
                   preferences.putFloat("var32", Escala7);
                   preferences.putFloat("var40", Promedio[6]);  
                   break;
           case 7:
                   preferences.putFloat("var8", valorVlinea);
                   preferences.putString("var17", VARIABLE8);
                   preferences.putString("var25", UNIDAD8);
                   preferences.putFloat("var33", Escala8);
                   preferences.putFloat("var41", Promedio[7]);  
                   break;
           case 8: 
                   preferences.putFloat("var42", CalADC1);
                   break;
           case 9: 
                   preferences.putFloat("var43", CalADC2);
                   break;
           case 10:  
                   preferences.putFloat("var44", CalADC3);
                   break;
           case 11:  
                   preferences.putFloat("var45", CalADC4);
                   break;
           case 12:
                   preferences.putFloat("var46", CalADC5);
                   break;
           case 13: 
                   preferences.putFloat("var47", CalADC6); 
                   break;
           case 14:  
                   preferences.putFloat("var48", CalADC7);
                   break;
           case 15:
                   preferences.putFloat("var49", CalADC8);
                   break;
           case 16:
                   preferences.putString("var51", TIPOEQUIPO);
                   break;
           case 50:
                   preferences.putFloat("var50", bitsResolucion);
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
                   preferences.putFloat("var50", bitsResolucion);
                  break;
           default:
                   break;
  }
  preferences.end();
 }
