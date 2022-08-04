#include <Arduino.h>
#include "mux.h"

/////////////////////////////////////////////////////SETUP///////////////////////////////////////////////////
//Inicializacion del multiplexor
void setup_mux(){
  pinMode(channelA, OUTPUT);
  pinMode(channelB, OUTPUT);
  //pinMode(channelC, OUTPUT);

  digitalWrite(channelA, LOW);
  digitalWrite(channelB, LOW);
  //digitalWrite(channelC, LOW);
}
/////////////////////////Seleccion del canal del multiplexor/////////////////////////
//Con los 3 digitalWrite de cada case, se selecciona con los pines de control del mux, el canal que se va a leer
void selectChannelMux(int canal){
  switch(canal){
    case 0:                           
            digitalWrite(channelA, 0);//         C B A  
            digitalWrite(channelB, 0);//         0 0 0
            //digitalWrite(channelC, 0);
            Serial.println("##-MUX CANAL 0-##");
            delay(100);
            break; 
    case 1:
            digitalWrite(channelA, 1);//         C B A
            digitalWrite(channelB, 0);//         0 0 1
            //digitalWrite(channelC, 0);
            Serial.println("##-MUX CANAL 1-##");
            delay(100);
            break;
    case 2:
            digitalWrite(channelA, 0);//         C B A
            digitalWrite(channelB, 1);//         0 1 0
            //digitalWrite(channelC, 0);
            Serial.println("##-MUX CANAL 2-##");
            delay(100);
            break;
    case 3:
            digitalWrite(channelA, 1);//         C B A
            digitalWrite(channelB, 1);//         0 1 1
            //digitalWrite(channelC, 0);
            Serial.println("##-MUX CANAL 3-##");
            delay(100);
            break;
/*  case 4:
            digitalWrite(channelA, 0);//         C B A
            digitalWrite(channelB, 0);//         1 0 0
            digitalWrite(channelC, 1);
            Serial.println("##-MUX CANAL 4-##");
            break;
    case 5:
            digitalWrite(channelA, 1);//         C B A
            digitalWrite(channelB, 0);//         1 0 1
            digitalWrite(channelC, 1);
            Serial.println("##-MUX CANAL 5-##");
            break; 
    case 6:
            digitalWrite(channelA, 0);//         C B A
            digitalWrite(channelB, 1);//         1 1 0
            digitalWrite(channelC, 1);
            Serial.println("##-MUX CANAL 6-##");
            break;
    case 7:
            digitalWrite(channelA, 1);//         C B A
            digitalWrite(channelB, 1);//         1 1 1
            digitalWrite(channelC, 1);
            Serial.println("##-MUX CANAL 7-##");
            break; */
  }
}
