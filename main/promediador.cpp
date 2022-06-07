#include <Arduino.h>
//Mux
#define channelA 5
#define channelB 6
#define channelC 7
#define MUESTRAS 10

void setup_mux()
{
pinMode(channelA, OUTPUT);
pinMode(channelB, OUTPUT);
pinMode(channelC, OUTPUT);

digitalWrite(channelA, LOW);
digitalWrite(channelB, LOW);
digitalWrite(channelC, LOW);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
float readyprom(int canal){
  
  float valoresPromedio;
  float acumprom=0; 
  int j=0;

    switch(canal)
    {
      
      case 0: 
              digitalWrite(channelA, 0);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 0);
              delay(50);
              break; 
      case 1:
      
              digitalWrite(channelA, 1);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 0);
              delay(50);
              break;
      case 2:
      
              digitalWrite(channelA, 0);
              digitalWrite(channelB, 1);
              digitalWrite(channelC, 0);
              delay(50);
              break;
      case 3:
      
              digitalWrite(channelA, 1);
              digitalWrite(channelB, 1);
              digitalWrite(channelC, 0);
              delay(50);
              break;
    /*  case 4:
      
              digitalWrite(channelA, 0);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 1);
              delay(50);
              break;
      case 5:
      
              digitalWrite(channelA, 1);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 1);
              delay(10);
              break;
              */
      }
 
    for(j=0;j<MUESTRAS;j++)
    {
    valoresPromedio = analogRead(0); //Leemos el pin analógico Ai  
    acumprom+= valoresPromedio ;
    }
    valoresPromedio = acumprom / MUESTRAS;
    acumprom = 0;
    return valoresPromedio;
  }

  
