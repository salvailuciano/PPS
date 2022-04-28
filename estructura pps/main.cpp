/**********************************
 *  LaBuhardillaDelLoco.xyz
 *  http://bit.ly/2MTrGne
 *  
 **********************************/

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



/*
LiquidLine linea1(1, 0, "Valores 1");
LiquidLine linea4(1, 1, "Modificar Parametro");
LiquidScreen pantalla1(linea1,linea4);

LiquidLine linea1_2(1, 0);
LiquidLine linea2_2(1, 0);
LiquidLine linea3_2(1, 0);
LiquidScreen pantalla2(linea1_2,linea2_2,linea3_2);

LiquidLine linea1_3(1, 0, "Opcion1");
LiquidLine linea2_3(1, 0, "Opcion2");
LiquidLine linea3_3(1, 0, "Atras");
LiquidScreen pantalla3(linea1_3,linea2_3,linea3_3);

LiquidMenu menu(lcd,pantalla1,pantalla2,pantalla3);
*/
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
/*  
 lcd.init();
//  lcd.begin();
  lcd.backlight();
  

  menu.init();

  linea1.set_focusPosition(Position::LEFT); 
  linea4.set_focusPosition(Position::LEFT); 
   
  linea1.attach_function(1,fn_led1); 
  linea4.attach_function(1,fn_led2); 
  menu.add_screen(pantalla1);

  linea1_2.set_focusPosition(Position::LEFT); 
  linea2_2.set_focusPosition(Position::LEFT); 
  linea3_2.set_focusPosition(Position::LEFT); 
  
  linea1_2.attach_function(1, fn_atras);
  linea2_2.attach_function(1, fn_atras);
  linea3_2.attach_function(1, fn_atras); 
  
  menu.add_screen(pantalla2);

  linea1_3.set_focusPosition(Position::LEFT); 
  linea2_3.set_focusPosition(Position::LEFT); 
  linea3_3.set_focusPosition(Position::LEFT); 
  
  linea1_3.attach_function(1, fn_atras);
  linea2_3.attach_function(1, fn_atras);
  linea3_3.attach_function(1, fn_atras); 
   
  menu.add_screen(pantalla3);
  

  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);
  pantalla3.set_displayLineCount(2);

  menu.set_focusedLine(0);


  menu.update();
*/
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

  /*
  stateA = digitalRead(outputA); 
    if (stateA != stateB){     
      if (digitalRead(outputB) != stateA) { 

        menu.switch_focus(true);
      } else {
   
        menu.switch_focus(false);
      }
      if(page_counter!=0)
      {
       if (digitalRead(outputB) != stateA) { 
       page_counter= page_counter -1; 
      } else {
        page_counter= page_counter +1;
      }
      if (page_counter>3) page_counter=1;
      if (page_counter<1) page_counter=3;
      }
      menu.update();
      stateB = stateA;
  }*/
  
  mostrarValores();
  //if(page_counter!=0) 
}
////////////////////////////////////////////////////////////FUNCIONES//////////////////////////////////////////////////////////////////
/*
//Funciones:::::
void selectOption(){
  if(digitalRead(sw) == LOW){
     lcd.clear(); 
      menu.call_function(1);
      delay(500);
  }
}
*/
/*
void fn_led1(){
   
  page_counter = 1;
  Valores();
  lcd.clear();  
  menu.change_screen(2);
  menu.set_focusedLine(0);
}

void fn_led2(){
  menu.change_screen(3);
  menu.set_focusedLine(0);

}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrarValores(){
 /*switch (page_counter) {
   
    case 1:{     //Design of home page 1
      
      lcd.setCursor(0,0);
      lcd.print("Isal:"); lcd.print(corriente,0); lcd.print("A");
   
      lcd.setCursor(9,0);
        
      lcd.print("Pd:");
      if (potenciad<=200)
      {
      lcd.print(potenciad,0); 
      lcd.print("W");
      }
      else
      lcd.print("200W"); 
      
      lcd.setCursor(0,1);
      lcd.print("Vex:"); lcd.print(vex,0); lcd.print("V");
      
      lcd.setCursor(9,1);
      lcd.print("AG:"); lcd.print(agc,1); lcd.print("V");
    }
    break;

    case 2: { //Design of page 2 
     lcd.setCursor(0,0);
     lcd.print("This is");
     lcd.setCursor(0,1);
     lcd.print("Page 2");
    }
    break;

    case 3: {   //Design of page 3 
     lcd.setCursor(0,0);
     lcd.print("You are now on");
     lcd.setCursor(0,1);
     lcd.print("Page 3");
    }
    break;
    
  }//switch end
*/

Serial.print("corriente: ");
Serial.println(corriente);
Serial.print("potenciad: ");
Serial.println(potenciad);
Serial.print("vex: ");
Serial.println(vex);
Serial.print("agc: ") ;
Serial.println(agc);
Serial.print("valor5: ") ;
Serial.println(valor5);
Serial.print("valor6: ") ;
Serial.println(valor6);
delay(200);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void fn_atras(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
  page_counter=0;
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
