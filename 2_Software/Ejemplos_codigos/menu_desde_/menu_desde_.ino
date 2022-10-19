/**********************************
 *  LaBuhardillaDelLoco.xyz
 *  http://bit.ly/2MTrGne
 *  
 **********************************/

#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

//ENCODER
#define outputA 3
#define outputB 4
#define sw 8

const float Iparametro  = 0.1;
//const float Pdparametro  = 1033.05;//(v*v/100)*pdparametro
const float Pdparametro  = 1250;
const float Vexparametro  = 0.1;
const float Agcparametro  = 1;

const int numReadings = 10; 

int aState;
int aLastState;  
int i=0;

float vout = 0.0; //Definimos la variable Vout
float aux = 0.0; //Definimos la variable Vout
float corriente = 0.0; //Definimos la variable Vin
float potenciad = 0.0; //Definimos la variable Vin
float vex = 0.0; //Definimos la variable Vin
float agc = 0.0; //Definimos la variable Vin
int iprom=0,prom=0;

int lectura[8]  ;//Definimos la variable value

int page_counter=0 ;       //To move beetwen pages
int led_seleccionado = 0;



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

void setup() {
  
pinMode(sw,INPUT_PULLUP);
  
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

}

void loop() {
 
  for(i=0;i<4;i++)
  {
    lectura[i] = analogRead(i); //Leemos el pin analógico Ai  
    }
     
  vout = (lectura[0] * 5.0) / 1024.0; // Cálculo para obtener el Vout //Valor * voltaje/BitsADC
  corriente = vout /Iparametro; // Cálculo para obtener Vin del divisor de tensión

  vout = (lectura[1] * 5.0) / 1024.0; // Cálculo para obtener el Vout //Valor * voltaje/BitsADC
  vout = (vout*vout)/100;
  potenciad = vout *Pdparametro; // Cálculo para obtener Vin del divisor de tensión
  
  vout = (lectura[2] * 5.0) / 1024.0; // Cálculo para obtener el Vout //Valor * voltaje/BitsADC
  vex = vout /Iparametro; // Cálculo para obtener Vin del divisor de tensión
  
  vout = (lectura[3] * 5.0) / 1024.0; // Cálculo para obtener el Vout //Valor * voltaje/BitsADC
  agc = vout /Agcparametro; // Cálculo para obtener Vin del divisor de tensión
  
  selectOption();
  delay(200);
  aState = digitalRead(outputA); 
    if (aState != aLastState){     
      if (digitalRead(outputB) != aState) { 

        menu.switch_focus(true);
      } else {
   
        menu.switch_focus(false);
      }
      if(page_counter!=0)
      {
       if (digitalRead(outputB) != aState) { 
       page_counter= page_counter -1; 
      } else {
        page_counter= page_counter +1;
      }
      if (page_counter>3) page_counter=1;
      if (page_counter<1) page_counter=3;
      }
      menu.update();
      aLastState = aState;
  }
  if(page_counter!=0) Valores();
}

//Funciones:::::
void selectOption(){
  if(digitalRead(sw) == LOW){
     lcd.clear(); 
      menu.call_function(1);
      delay(500);
  }
}

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


void Valores(){
 switch (page_counter) {
   
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
  
}


void fn_atras(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
  page_counter=0;
}
