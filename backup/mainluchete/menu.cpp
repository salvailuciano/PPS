#include <Arduino.h>
#include "menu.h"
#include "Button.h"
#include "definesConfiguraciones.h"
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

const int cantidadMediciones = 4;

int medicion=1 ;       //Variable que indica si esta en modo medicion o configuracion
int page_counter=1 ;       //To move beetwen pages
float analogValue[cantidadMediciones];
/*
 * The Button class is not a part of the LiquidMenu library. The first
 * parameter is the button's pin, the second enables or disables the
 * internal pullup resistor (not required) and the third is the debounce
 * time (not required).
 */
//////////////////////////////////////////////DECLARACION DE BOTONES//////////////////////////////////////////////////
// Button objects instantiation
const bool pullup = true;
//Button left(12, pullup);
//Button right(11, pullup);
Button up(10, pullup);
Button down(9, pullup);
Button enter(8, pullup);

//////////////////////////////////////////////MENUES Y CONTENIDO//////////////////////////////////////////////////
LiquidLine linea1(1, 0, "Valores 1");
LiquidLine linea4(1, 1, "Modificar Parametro");
LiquidScreen pantalla1(linea1,linea4);

LiquidLine linea1_2(1, 0);
LiquidLine linea2_2(1, 0);
LiquidLine linea3_2(1, 0);
LiquidScreen pantalla2(linea1_2,linea2_2,linea3_2);
/*
LiquidLine analog_line1_2(1, 0, VARIABLE1, analogValue[0]);
LiquidLine analog_line2_2(1, 0, VARIABLE2, analogValue[1]);
LiquidLine analog_line3_2(1, 0, VARIABLE3, analogValue[2]);
LiquidLine analog_line4_2(1, 0, VARIABLE4, analogValue[3]);
LiquidScreen pantalla2(analog_line1_2,analog_line2_2,analog_line3_2,analog_line4_2);
*/

LiquidLine linea1_3(1, 0, "Opcion1");
LiquidLine linea2_3(1, 0, "Opcion2");
LiquidLine linea3_3(1, 0, "Atras");
LiquidScreen pantalla3(linea1_3,linea2_3,linea3_3);

LiquidMenu menu(lcd,pantalla2,pantalla1,pantalla3);
//////////////////////////////////////FUNCIONES LIGADAS AL MENU//////////////////////////////////////////////////
void setup_menu(){
  lcd.init();
  //lcd.begin();
  lcd.backlight();
  //pinMode(Enter,INPUT_PULLUP);
  
  menu.init();
  linea1.set_focusPosition(Position::LEFT); 
  linea4.set_focusPosition(Position::LEFT); 
   
  linea1.attach_function(1,fn_mediciones); 
  linea4.attach_function(1,fn_mas_configuraciones); 
  menu.add_screen(pantalla1);
  /*
  analog_line1_2.set_focusPosition(Position::LEFT); 
  analog_line2_2.set_focusPosition(Position::LEFT); 
  analog_line3_2.set_focusPosition(Position::LEFT); 
  analog_line4_2.set_focusPosition(Position::LEFT); 
  
  analog_line1_2.attach_function(1, fn_configuracion);
  analog_line2_2.attach_function(1, fn_configuracion);
  analog_line3_2.attach_function(1, fn_configuracion); 
  analog_line4_2.attach_function(1, fn_configuracion); 
  menu.add_screen(pantalla2);
  /*/

  linea1_2.set_focusPosition(Position::LEFT); 
  linea2_2.set_focusPosition(Position::LEFT); 
  linea3_2.set_focusPosition(Position::LEFT); 
  
  linea1_2.attach_function(1, fn_configuracion);
  linea2_2.attach_function(1, fn_configuracion);
  linea3_2.attach_function(1, fn_configuracion); 
  
  menu.add_screen(pantalla2);
   
  linea1_3.set_focusPosition(Position::LEFT); 
  linea2_3.set_focusPosition(Position::LEFT); 
  linea3_3.set_focusPosition(Position::LEFT); 
  
  linea1_3.attach_function(1, fn_configuracion);
  linea2_3.attach_function(1, fn_configuracion);
  linea3_3.attach_function(1, fn_configuracion); 
   
  menu.add_screen(pantalla3);
  
  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);
  pantalla3.set_displayLineCount(2);
  menu.set_focusedLine(0);
  menu.update();
}



///////////////////////////////////////////////////////FUNCION BOTONES//////////////////////////////////////////////////////////////////  
 void leerBotones(){

// Check all the buttons
/* if (right.check() == LOW) {
    Serial.println(F("RIGHT button pressed"));
    menu.next_screen();
  }
  if (left.check() == LOW) {
    Serial.println(F("LEFT button pressed"));
    menu.previous_screen();
  }*/
  
  if (up.check() == LOW) {
    Serial.println(F("UP button pressed"));
    // Calls the function identified with one
    // for the focused line.
    menu.switch_focus(false);
    if(medicion!=0){
    page_counter= page_counter -1;
    }
  }
  if (down.check() == LOW) {
    Serial.println(F("DOWN button pressed"));
     menu.switch_focus(true);
     if(medicion!=0){
     page_counter= page_counter +1;
     }
  }
  if (enter.check() == LOW) {
    Serial.println(F("ENTER button pressed"));
    // Switches focus to the next line.
   menu.call_function(1);
    
  }
      if (page_counter>3){
        page_counter=1;
      }
      if (page_counter<1){
        page_counter=3;
      }   
 }


///////////////////////////////////////////////////////FUNCION PARA MOSTRAR VALORES EN PANTALLA////////////////////////////////////////////////////////////////// 

void mostrarValores(float a,float b,float c,float d){
  
  if(medicion!=0){// si no esta en modo medicion procede a mostrar los valores
  
  switch (page_counter){
    case 1: //Design of home page 1     
      lcd.setCursor(0,0);
      lcd.print(VARIABLE1); lcd.print(a,0); lcd.print("A");
      lcd.setCursor(0,1);
      lcd.print(VARIABLE2);
      if (b<=200){
        lcd.print(b,0); 
        lcd.print("W");
      }
      else{
        lcd.print("200W"); 
      }
      delay(100);
      break;
    case 2: //Design of page 2
      lcd.setCursor(0,0);
      lcd.print(VARIABLE3); lcd.print(c,0); lcd.print("V");
      lcd.setCursor(0,1);
      lcd.print(VARIABLE4); lcd.print(d,1); lcd.print("V");
      delay(100);
      break;
    case 3: //Design of page 3 
      lcd.setCursor(0,0);
      lcd.print("You are now on");
      lcd.setCursor(0,1);
      lcd.print("Page 3");
      delay(100);
      break;
    }
  }
}

///////////////////////////////////////////////////////FUNCIONES//////////////////////////////////////////////////////////////////
/*void selectOption(){
  if(enter.check() == LOW){
    lcd.clear(); 
    menu.call_function(1);
   // delay(500);
  }
}*/
/////////////////////////////
void fn_mediciones(){
  lcd.clear(); 
  medicion=1;
  page_counter=1; 
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

/////////////////////////////
void fn_configuracion(){
  medicion=0;
  lcd.clear(); 
  menu.change_screen(2);
  menu.set_focusedLine(0);
  
}
/////////////////////////////
void fn_mas_configuraciones(){
  menu.change_screen(3);
  menu.set_focusedLine(0);
}


 
