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

int aState;
int aLastState;  

float corriente = 0;
float voltaje = 0;
float potencia = 0;
float energia = 0;



int analogInput = 0; //Definimos el pin analógico A0 para la lectura del voltaje
float vout = 0.0; //Definimos la variable Vout
float vin = 0.0; //Definimos la variable Vin
float R1 = 100000.0; //  R1 (100K) Valor de la resistencia R1 del divisor de tensión
float R2 = 10000.0; //  R2 (10K) Valor de la resistencia R2 del divisor de tención
int value = 0;//Definimos la variable value
int pinA4_value = 0,pinA5_value=1;//Definimos la variable value


int led_seleccionado = 0;
const float pi = 3.14159265f;

LiquidLine linea1(1, 0, "V: ", pinA4_value);
LiquidLine linea2(1, 0, "A: ", pinA5_value);
LiquidLine linea3(1, 0, "W");
LiquidLine linea4(1, 1, "Wh");
LiquidScreen pantalla1(linea1, linea2,linea3,linea4);

LiquidLine linea1_2(1, 0, "ON");
LiquidLine linea2_2(1, 1, "OFF");
LiquidLine linea3_2(1, 0, "Atras");
LiquidScreen pantalla2(linea1_2,linea2_2,linea3_2);

LiquidMenu menu(lcd,pantalla1,pantalla2);

void setup() {

  
  pinMode(sw,INPUT_PULLUP);
  
 lcd.init();
//  lcd.begin();
  lcd.backlight();
  

  menu.init();

  linea1.set_focusPosition(Position::LEFT); 
  linea2.set_focusPosition(Position::LEFT); 
  linea3.set_focusPosition(Position::LEFT); 
  linea4.set_focusPosition(Position::LEFT); 
   
  linea1.attach_function(1, fn_led1); 
  linea2.attach_function(1, fn_led2);
  linea3.attach_function(1, fn_led3);
  linea4.attach_function(1, fn_todos);


 
  menu.add_screen(pantalla1);
  
   lcd.setCursor(9,0);
  lcd.print(corriente); lcd.print(" A");
  
  linea1_2.set_focusPosition(Position::LEFT); 
  linea2_2.set_focusPosition(Position::LEFT); 
  linea3_2.set_focusPosition(Position::LEFT); 
  
  linea1_2.attach_function(1, fn_on); 
  linea2_2.attach_function(1, fn_off);
  linea3_2.attach_function(1, fn_atras);
   
  menu.add_screen(pantalla2);

  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);

  menu.set_focusedLine(0);

  menu.update();

}

void loop() {


 
  selectOption();

  aState = digitalRead(outputA); 
    if (aState != aLastState){     
      if (digitalRead(outputB) != aState) { 
        menu.switch_focus(false);
      } else {
        menu.switch_focus(true);
      }
      menu.update();
      aLastState = aState;
  }

}





//Funciones:::::
void selectOption(){
  if(digitalRead(sw) == LOW){
      menu.call_function(1);
      delay(500);
  }
}

void fn_led1(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
  led_seleccionado = 1;
}

void fn_led2(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
  led_seleccionado = 2;
}


void fn_led3(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
  led_seleccionado = 3;
}


void fn_todos(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
  led_seleccionado = 0;
}

void fn_on(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
  led_seleccionado = 0;
}
void fn_off(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
  led_seleccionado = 0;
}


void fn_atras(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
}
