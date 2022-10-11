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


int calibracionesGenerales(){
  Serial.println("//////////////////////////////////////");
  Serial.println("//    Configuracion de Parametros   //");
  Serial.println("//////////////////////////////////////");
  Serial.println("//   Ingrese variable a modificar   //");
  Serial.println("//                o                 //");
  Serial.println("// Un caracter aleatorio para salir //");
  Serial.println("//////////////////////////////////////");
  waitForUserInput();
     if (command.equals("001")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 1:");
        waitForUserInput();
        //command.trim();
        Serial.println(command);
        VARIABLE1 = command;
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
        writeEEPROMVariables(2);
      }
      else if (command.equals("004")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 4:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE4 = command;
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
        writeEEPROMVariables(4);
      }
      else if (command.equals("006")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 6:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE6 = command;
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
        writeEEPROMVariables(6);
      }
      else if (command.equals("008")){
        resetInput();
        Serial.println("Ingrese el nombre de la variable 8:");
        waitForUserInput();
        Serial.println(command);
        VARIABLE8 = command;
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
      else {
        Serial.println("Salir");
         return 1;
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
