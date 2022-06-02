#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

#define MUESTRAS 10

//ENCODER
//#define outputA 3
//#define outputB 4
#define sw 8

//Mux
#define channelA 5
#define channelB 6
#define channelC 7


const float Iparametro  = 0.1;
//const float Pdparametro  = 1033.05;//(v*v/100)*pdparametro
const float Pdparametro  = 1250;
const float Vexparametro  = 0.1;
const float Agcparametro  = 1;
int stateA=0,stateB=0;
const int numReadings = 10; 

 

float corriente = 0.0; //Definimos la variable Vin
float potenciad = 0.0; //Definimos la variable Vin
float vex = 0.0; //Definimos la variable Vin
float agc = 0.0; //Definimos la variable Vin
float valor5 = 0;
float valor6 = 0;

int page_counter=0 ;       //To move beetwen pages

////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////
void setup() {

Serial.begin(9600);
Serial.println(F("Initialize System"));

pinMode(sw,INPUT_PULLUP);

pinMode(channelA, OUTPUT);
pinMode(channelB, OUTPUT);
pinMode(channelC, OUTPUT);

digitalWrite(channelA, LOW);
digitalWrite(channelB, LOW);
digitalWrite(channelC, LOW);
 
 lcd.init();
 lcd.begin();
 lcd.backlight();
}
////////////////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
void loop() {

  float aux = 0.0; //Definimos la variable auxiliar
  int i=0;
  float lectura[5]  ;//Definimos la variable value

   for(i=0;i<6;i++)
  {
       lectura[i]= readyprom(i);
  
  }
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
  
  //selectOption();
  
  mostrarValores();
  //if(page_counter!=0) 
}
