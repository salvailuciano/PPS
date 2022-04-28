//Promediador

for(j=0;j<MUESTRAS;j++)
    {
    valoresPromedio = analogRead(0); //Leemos el pin analógico Ai  
    acumprom+= valoresPromedio ;
    }
    valoresPromedio = acumprom / MUESTRAS;
    acumprom = 0;
    return valoresPromedio;
  }
