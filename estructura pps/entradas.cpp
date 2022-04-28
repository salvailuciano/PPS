const float Iparametro  = 0.1;
//const float Pdparametro  = 1033.05;//(v*v/100)*pdparametro
const float Pdparametro  = 1250;
const float Vexparametro  = 0.1;
const float Agcparametro  = 1;
int stateA=0,stateB=0;
const int numReadings = 10; 

  Serial.println("calculando");
  //aux = (lectura[0] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  //corriente = aux /Iparametro; // Cálculo para obtener Vin del divisor de tensión
  corriente = (lectura[0]*5) / 1024;
  //aux = (lectura[1] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  //aux = (aux*aux)/100;
  //potenciad = aux *Pdparametro; // Cálculo para obtener Vin del divisor de tensión
  potenciad = (lectura[1]*5) / 1024;
  //aux = (lectura[2] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  //vex = aux /Iparametro; // Cálculo para obtener Vin del divisor de tensión
  vex = (lectura[2]*5) / 1024;
  //aux = (lectura[3] * 5.0) / 1024.0; // Cálculo para obtener el aux //Valor * voltaje/BitsADC
  //agc = aux /Agcparametro; // Cálculo para obtener Vin del divisor de tensión
  agc = (lectura[3]*5) / 1024;

  valor5 = (lectura[4]*5) / 1024;
  valor6 = (lectura[5]*5) / 1024;
