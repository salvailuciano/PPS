float readyprom(int canal){
  
  float valoresPromedio;
  float acumprom=0; 
  int j=0;
Serial.println(canal);
    switch(canal)
    {
      
      case 0: 
              digitalWrite(channelA, 0);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 0);
              delay(200);
              break; 
      case 1:
      
              digitalWrite(channelA, 1);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 0);
              delay(200);
              break;
      case 2:
      
              digitalWrite(channelA, 0);
              digitalWrite(channelB, 1);
              digitalWrite(channelC, 0);
              delay(200);
              break;
      case 3:
      
              digitalWrite(channelA, 1);
              digitalWrite(channelB, 1);
              digitalWrite(channelC, 0);
              delay(200);
              break;
      case 4:
      
              digitalWrite(channelA, 0);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 1);
              delay(200);
              break;
      case 5:
      
              digitalWrite(channelA, 1);
              digitalWrite(channelB, 0);
              digitalWrite(channelC, 1);
              delay(200);
              break;
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

