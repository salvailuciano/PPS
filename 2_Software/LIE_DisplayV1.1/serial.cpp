#include "definesConfiguraciones.h"
#include "eeprom.h"

//////////////////////////Comunicacion serial///////////////////////////////
//  En este programa se describe la comunicacion serial y su funcionamiento:
/*
El proposito de la comunicacion serial es que a travez de un monitor serial
se pueda modificar tanto los valores maximos a mostrar en el display
como la posibilidad de configuraciones y monitoreo:

Se puede por un lado monitorear los datos del sistema tanto:
-Mediciones en tiempo real
-Valor puro del adc en cuentas
-Nombres asignados a las variables

Por otro lado se pueden modificar los parametros de medicion:

Esto se realiza de la siguiente forma:

Se envia un codigo especifico a la configuracion que se quiere modificar.
Luego el sistema responde para guardar la variable en la memoria eeprom
y finalmente se actualiza lo que se modifico

Los codigos que se programaron para la comunicacion serial son:

-001 Se cambia el nombre de la variable 1 y la unidad de esta medicion
-002 Se cambia el nombre de la variable 2 y la unidad de esta medicion
-003 Se cambia el nombre de la variable 3 y la unidad de esta medicion
-004 Se cambia el nombre de la variable 4 y la unidad de esta medicion
-005 Se cambia el nombre de la variable 5 y la unidad de esta medicion
-006 Se cambia el nombre de la variable 6 y la unidad de esta medicion
-007 Se cambia el nombre de la variable 7 y la unidad de esta medicion
-008 Se cambia el nombre de la variable 8 y la unidad de esta medicion
-009 Se cambia el valor de la variable 1 que se mostrara a full scale del adc
-010 Se cambia el valor de la variable 2 que se mostrara a full scale del adc
-011 Se cambia el valor de la variable 3 que se mostrara a full scale del adc
-012 Se cambia el valor de la variable 4 que se mostrara a full scale del adc
-013 Se cambia el valor de la variable 5 que se mostrara a full scale del adc
-014 Se cambia el valor de la variable 6 que se mostrara a full scale del adc
-015 Se cambia el valor de la variable 7 que se mostrara a full scale del adc
-016 Se cambia el valor de la variable 8 que se mostrara a full scale del adc
-017 Se muestran los valores en tiempo real de todas las mediciones
-018 Se muestran los valores del adc de todas las variables
-020 Se muestran todos los valores full scale configurados
-030 Se puede configurar y modificar los bits de resolucion del adc de 9 a 12 bits
-098 Se puede borrar la memoria eeprom y descartar los cambios que se hayan realizado

El objetivo principal de este modo serial es la posibilidad de configurar el dispositivo
sin cambiar el codigo y reprogramar el mirocontrolador. 
*/



void waitForUserInput();
void resetInput();
String  command;
bool userInput = false;
extern float bitsResolucion; 
extern bool flagValores;
extern bool  flagADC;

int calibracionesGenerales(){
   Serial.println();
  Serial.println("//////////////////////////////////////");
  Serial.println("//    Configuracion de Parametros   //");
  Serial.println("//////////////////////////////////////");
  Serial.println("//   Ingrese variable a modificar   //");
  Serial.println("//                o                 //");
  Serial.println("// Un caracter aleatorio para salir //");
  Serial.println("//////////////////////////////////////");
  waitForUserInput();
  command.trim();
  
     if (command.equals("001")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 1:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        VARIABLE1 = command;
        resetInput();
        Serial.println("Ingrese la unidad de la variable 1:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD1 = command;
       // Serial.println("Listo");
        resetInput();
        Serial.println("Ingrese valor full escala de la variable 1:");
        waitForUserInput();
        Serial.println(command);
        valorPD =command.toFloat();
        resetInput();

        Serial.println("Ingrese la escala de la variable 1:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala1 =command.toFloat();
        resetInput();

        Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[0] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(0);
        }

      else if (command.equals("002")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 2:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE2 = command;
        resetInput();
        
        Serial.println("Ingrese la unidad de la variable 2:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD2 = command;
        resetInput();
        
        Serial.println("Ingrese valor full escala de la variable 2:");
        waitForUserInput();
        Serial.println(command);
        valorPR = command.toFloat();
        resetInput();
        
        Serial.println("Ingrese la escala de la variable 2:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala2 =command.toFloat();
        resetInput();
        
        Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[1] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(1);
      }
      else if (command.equals("003")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 3:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE3 = command;
        resetInput();
        
        Serial.println("Ingrese la unidad de la variable 3:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD3 = command;
        resetInput();
        
        Serial.println("Ingrese valor full escala de la variable 3:");
        waitForUserInput();
        Serial.println(command);
        valorAGC = command.toFloat();
        resetInput();
        
        Serial.println("Ingrese la escala de la variable 3:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala3 =command.toFloat();
        resetInput();

       Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[2] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(2);
      }
      else if (command.equals("004")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 4:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE4 = command;
        resetInput();
        
        Serial.println("Ingrese la unidad de la variable 4:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD4 = command;
        resetInput();
        
        Serial.println("Ingrese valor full escala de la variable 4:");
        waitForUserInput();
        Serial.println(command);
        valorIsal = command.toFloat();
        resetInput();
        
        Serial.println("Ingrese la escala de la variable 4:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala4 =command.toFloat();
        resetInput();

        Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[3] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(3);
      }
      else if (command.equals("005")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 5:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE5 = command;
        resetInput();
        
        Serial.println("Ingrese la unidad de la variable 5:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD5 = command;
        resetInput();
        
        Serial.println("Ingrese valor full escala de la variable 5:");
        waitForUserInput();
        Serial.println(command);
        valorVsal = command.toFloat();
        resetInput();

        Serial.println("Ingrese la escala de la variable 5:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala5 =command.toFloat();
        resetInput();
        
        Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[4] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(4);
      }
      else if (command.equals("006")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 6:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE6 = command;
        resetInput();
        
        Serial.println("Ingrese la unidad de la variable 6:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD6 = command;
        resetInput();
        
        Serial.println("Ingrese valor full escala de la variable 6:");
        waitForUserInput();
        Serial.println(command);
        valorVexc = command.toFloat();
        resetInput();

        Serial.println("Ingrese la escala de la variable 6:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala6 =command.toFloat();
        resetInput();
        
        Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[5] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(5);
      }
      else if (command.equals("007")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 7:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE7 = command;
        resetInput();
        
        Serial.println("Ingrese la unidad de la variable 7:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD7 = command;
        resetInput();
        
        Serial.println("Ingrese valor full escala de la variable 7:");
        waitForUserInput();
        Serial.println(command);
        valorVaux = command.toFloat();
        resetInput();

        Serial.println("Ingrese la escala de la variable 7:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala7 =command.toFloat();
        resetInput();
        
        Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[6] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(6);
      }
      else if (command.equals("008")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 8:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE8 = command;
        resetInput();
        
        Serial.println("Ingrese la unidad de la variable 8:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD8 = command;
        resetInput();
        
        Serial.println("Ingrese valor full escala de la variable 8:");
        waitForUserInput();
        Serial.println(command);
        valorVlinea = command.toFloat();
        resetInput();

        Serial.println("Ingrese la escala de la variable 8:");
        Serial.println("Ingrese 0 para lineal 1 para cuadratica");
        waitForUserInput();
        Serial.println(command);
        Escala8 =command.toFloat();
        resetInput();

        Serial.println("Ingrese el numero de valores a promediar:");
        waitForUserInput();
        Serial.println(command);
        Promedio[7] =command.toFloat();
        resetInput();
        
        writeEEPROMVariables(7);
      }

      else if (command.equals("017")){
       flagValores=true;
       resetInput();
      }
      else if (command.equals("018")){
       flagADC=true;
       resetInput();
      }
      else if (command.equals("020")){
        
      Serial.println();
      Serial.print("1) Valor full scale Adc1: ");
      Serial.print(valorPD); 
      Serial.println(UNIDAD1);
      Serial.print("2) Valor full scale Adc2: ");
      Serial.print(valorPR);
      Serial.println(UNIDAD2);
      Serial.print("3) Valor full scale Adc3: ");
      Serial.print(valorAGC);
      Serial.println(UNIDAD3);
      Serial.print("4) Valor full scale Adc4: ");
      Serial.print(valorIsal);
      Serial.println(UNIDAD4);
      Serial.print("5) Valor full scale Adc5: ");
      Serial.print(valorVsal);
      Serial.println(UNIDAD5);
      Serial.print("6) Valor full scale Adc6: ");
      Serial.print(valorVexc);
      Serial.println(UNIDAD6);
      Serial.print("7) Valor full scaleAdc7: ");
      Serial.print(valorVaux);
      Serial.println(UNIDAD7);
      Serial.print("8) Valor full scale Adc8: ");
      Serial.print(valorVlinea);
      Serial.println(UNIDAD8);
      resetInput();
      }
      else if (command.equals("050")){
        resetInput();
        Serial.println("Ingrese bits de resolucion:");
        waitForUserInput();
        Serial.println(command);
        bitsResolucion = command.toFloat();
        resetInput();
        writeEEPROMVariables(50);
      }
      else if (command.equals("098")){
        resetInput();
        Serial.println("Borrando memoria EEPROM...");
        writeEEPROMVariables(98);
        
        Serial.println("Listo");
      }
      
      else {
        resetInput();
        Serial.println("¿Desea Salir?");
        Serial.println("Escriba no para cancelar o cualquier tecla para confirmar...");
        waitForUserInput();
        command.toLowerCase();
        command.trim();
        if (command.equals("no")){
        Serial.println(" ");
        resetInput();    
        }
        else{
         return 1;
        }
      }

      return 0;
    delay(10);     
}

void waitForUserInput(){
    while (!userInput){ 
        if (Serial.available() > 0){
            char c = (char)Serial.read();
            if (c != '\n' ){
                command += c;
            }
            else{
                userInput = true;
                return;
            }
        }
        if (digitalRead(5) == LOW){// si aprieto boton arriba cancela y sale
            userInput = true;
            return;
        }
    }
}


void resetInput(){
    userInput = false;
    command = "";
}
