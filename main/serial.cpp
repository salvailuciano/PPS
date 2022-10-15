#include "definesConfiguraciones.h"
#include <stdlib.h>
#include "eeprom.h"

void waitForUserInput();
void resetInput();
String  command;
bool userInput = false;
extern float valorPD;
extern float valorPR;
extern float valorAGC;
extern float valorIsal;
extern float valorVsal;
extern float valorVexc;
extern float valorVaux;
extern float valorVlinea;
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
        Serial.println("Ingrese la unidad de la variable 1:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD1 = command;
        Serial.println("Listo");
        resetInput();
        writeEEPROMVariables(0);
        }
      else if (command.equals("002")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 2:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE2 = command;
        Serial.println("Ingrese la unidad de la variable 2:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD2 = command;
        resetInput();
        writeEEPROMVariables(1);
      }
      else if (command.equals("003")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 3:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE3 = command;
        Serial.println("Ingrese la unidad de la variable 3:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD3 = command;
        resetInput();
        writeEEPROMVariables(2);
      }
      else if (command.equals("004")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 4:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE4 = command;
        Serial.println("Ingrese la unidad de la variable 4:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD4 = command;
        resetInput();
        writeEEPROMVariables(3);
      }
      else if (command.equals("005")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 5:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE5 = command;
        Serial.println("Ingrese la unidad de la variable 5:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD5 = command;
        resetInput();
        writeEEPROMVariables(4);
      }
      else if (command.equals("006")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 6:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE6 = command;
        Serial.println("Ingrese la unidad de la variable 6:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD6 = command;
        resetInput();
        writeEEPROMVariables(5);
      }
      else if (command.equals("007")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 7:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE7 = command;
        Serial.println("Ingrese la unidad de la variable 7:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD7 = command;
        resetInput();
        writeEEPROMVariables(6);
      }
      else if (command.equals("008")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 8:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE8 = command;
        Serial.println("Ingrese la unidad de la variable 8:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        UNIDAD8 = command;
        resetInput();
        writeEEPROMVariables(7);
      }
      
      else if (command.equals("009")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 1:");
        waitForUserInput();
        Serial.println(command);
        valorPD =command.toFloat();
        resetInput();
        writeEEPROMVariables(8);
      }
      else if (command.equals("010")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 2:");
        waitForUserInput();
        Serial.println(command);
        valorPR = command.toFloat();
        resetInput();
        writeEEPROMVariables(9);
      }
      else if (command.equals("011")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 3:");
        waitForUserInput();
        Serial.println(command);
        valorAGC = command.toFloat();
        resetInput();
        writeEEPROMVariables(10);
      }
      else if (command.equals("012")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 4:");
        waitForUserInput();
        Serial.println(command);
        valorIsal = command.toFloat();
        resetInput();
        writeEEPROMVariables(11);
      }
      else if (command.equals("013")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 5:");
        waitForUserInput();
        Serial.println(command);
        valorVsal ;
        resetInput();
        writeEEPROMVariables(12);
      }
      else if (command.equals("014")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 6:");
        waitForUserInput();
        Serial.println(command);
        valorVexc = command.toFloat();
        resetInput();
        writeEEPROMVariables(13);
      }
      else if (command.equals("015")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 7:");
        waitForUserInput();
        Serial.println(command);
        valorVaux = command.toFloat();
        resetInput();
        writeEEPROMVariables(14);
      }
     
      else if (command.equals("016")){
        resetInput();
        Serial.println("Ingrese valor a mostrar variable 8:");
        waitForUserInput();
        Serial.println(command);
        valorVlinea = command.toFloat();
        resetInput();
        writeEEPROMVariables(15);
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
      else if (command.equals("030")){
        resetInput();
        Serial.println("Ingrese bits de resolucion:");
        waitForUserInput();
        Serial.println(command);
        bitsResolucion = command.toFloat();
        resetInput();
        writeEEPROMVariables(30);
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
            if (c != '\n'){
                command += c;
            }
            else{
                userInput = true;
                return;
            }
        }
    }
}


void resetInput(){
    userInput = false;
    command = "";
}
