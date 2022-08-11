#include <Arduino.h>
#include "menu.h"
#include "Button.h"
#include "definesConfiguraciones.h"
#include <LiquidCrystal_I2C.h> //Descomentar para I2C
#include <LiquidCrystal.h> // Funcion para coneccion de LCD por piner de Datos
#include <LiquidMenu.h>

/*
The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

/////////////////////////////////LCD COMUN LUCHETE (NO I2C)//////////////////////////////
// Pin mapping for the display
//const byte LCD_RS = 32;
//const byte LCD_E = 33;
//const byte LCD_D4 = 27;
//const byte LCD_D5 = 4;   
//const byte LCD_D6 = 2;
//const byte LCD_D7 = 15;
//LCD R/W pin to ground
//10K potentiometer to VO
//LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
///////////////////////////////////////////////////////////////////////////////


LiquidCrystal_I2C lcd(0x3f, 16, 2); //Descomentar si se usa I2C

//const int cantidadMediciones = 4;

int flag_medicion=1 ;       //Variable que indica si esta en modo medicion o configuracion
int flag_temperatura=0 ;       //Variable que indica si esta en modo medicion o configuracion
int page_counter=1 ;       //To move beetwen pages
int cantidadPaginas=4;
/*
 * The Button class is not a part of the LiquidMenu library. The first
 * parameter is the button's pin, the second enables or disables the
 * internal pullup resistor (not required) and the third is the debounce
 * time (not required).
 */

///////////////////////////DECLARACION DE BOTONES//////////////////////////////////
// Button objects instantiatio
const bool pullup = true;
//Button left(12, pullup);
//Button right(11, pullup);
Button up(Bot_up, pullup);
Button down(Bot_down, pullup);
Button enter(Bot_enter, pullup);


//////////////////////////////////////////////MENUES Y CONTENIDO//////////////////////////////////////////////////
LiquidLine linea1(1, 0, "Mediciones");
LiquidLine linea2(1, 1, "Calibraciones");
LiquidLine linea3(1, 2, "Control PWM");
LiquidLine linea4(1, 3, "Temperatura");
LiquidScreen pantalla1(linea1,linea2,linea3,linea4);

LiquidLine linea1_2(1, 0);
LiquidLine linea2_2(1, 0);
LiquidLine linea3_2(1, 0);
LiquidLine linea4_2(1, 0);
LiquidScreen pantalla2(linea1_2,linea2_2,linea3_2,linea4_2);
/*
LiquidLine linea1_4(1, 0);
LiquidLine linea2_4(1, 0);
LiquidLine linea3_4(1, 0);
LiquidLine linea4_4(1, 0);
LiquidScreen pantalla4(linea1_4,linea2_4,linea3_4,linea4_4);
/*
LiquidLine analog_line1_2(1, 0, VARIABLE1, analogValue[0]);
LiquidLine analog_line2_2(1, 0, VARIABLE2, analogValue[1]);
LiquidLine analog_line3_2(1, 0, VARIABLE3, analogValue[2]);
LiquidLine analog_line4_2(1, 0, VARIABLE4, analogValue[3]);
LiquidScreen pantalla2(analog_line1_2,analog_line2_2,analog_line3_2,analog_line4_2);
*/

LiquidLine linea1_3(1, 0, "Tensiones");
LiquidLine linea2_3(1, 1, "Corrientes");
LiquidLine linea3_3(1, 2, "Potencia");
LiquidLine linea4_3(1, 3, "Atras");
LiquidScreen pantalla3(linea1_3,linea2_3,linea3_3,linea4_3);

LiquidLine linea1_4(1, 0);
LiquidScreen pantalla4(linea1_4);

//LiquidLine analog_line1_4(1, 0, "Temperatura", analogValue);
//LiquidScreen pantalla4(analog_line1_4);

LiquidMenu menu(lcd,pantalla2,pantalla1,pantalla3,pantalla4);
//////////////////////////////////////FUNCIONES LIGADAS AL MENU//////////////////////////////////////////////////
void setup_menu(){
  lcd.init(); //Descomentar para I2C
//lcd.begin(16, 2); //Comentar si se usa I2C
  lcd.backlight(); // Descomentar para I2C

  menu.init();
  linea1.set_focusPosition(Position::LEFT); 
  linea2.set_focusPosition(Position::LEFT); 
  linea3.set_focusPosition(Position::LEFT); 
  linea4.set_focusPosition(Position::LEFT); 
   
  linea1.attach_function(1,fn_mediciones); 
  linea2.attach_function(1,fn_mas_configuraciones); 
  linea3.attach_function(1,fn_mas_configuraciones); 
  linea4.attach_function(1,fn_temperatura); 
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
  linea4_2.set_focusPosition(Position::LEFT); 
  
  linea1_2.attach_function(1, fn_configuracion);
  linea2_2.attach_function(1, fn_configuracion);
  linea3_2.attach_function(1, fn_configuracion); 
  linea4_2.attach_function(1, fn_configuracion);
  
  menu.add_screen(pantalla2);
/*
  linea1_4.set_focusPosition(Position::LEFT); 
  linea2_4.set_focusPosition(Position::LEFT); 
  linea3_4.set_focusPosition(Position::LEFT); 
  linea4_4.set_focusPosition(Position::LEFT); 
  
  linea1_4.attach_function(1, fn_configuracion);
  linea2_4.attach_function(1, fn_configuracion);
  linea3_4.attach_function(1, fn_configuracion); 
  linea4_4.attach_function(1, fn_configuracion);
  */
//  menu.add_screen(pantalla4);
   
  linea1_3.set_focusPosition(Position::LEFT); 
  linea2_3.set_focusPosition(Position::LEFT); 
  linea3_3.set_focusPosition(Position::LEFT); 
  linea4_3.set_focusPosition(Position::LEFT);  
  
  linea1_3.attach_function(1, fn_configuracion);
  linea2_3.attach_function(1, fn_configuracion);
  linea3_3.attach_function(1, fn_configuracion); 
  linea4_3.attach_function(1, fn_configuracion); 
  
  menu.add_screen(pantalla3);

  linea1_4.set_focusPosition(Position::LEFT); 
  linea1_4.attach_function(1, fn_configuracion);
 //analog_line1_4.set_focusPosition(Position::LEFT); 
 // analog_line1_4.attach_function(1, fn_configuracion);
  menu.add_screen(pantalla4);
  
  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);
  pantalla3.set_displayLineCount(2);
  pantalla4.set_displayLineCount(2);
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
    if(flag_medicion!=0){
    page_counter= page_counter -1;
    }
  }
  if (down.check() == LOW) {
    Serial.println(F("DOWN button pressed"));
     menu.switch_focus(true);
     if(flag_medicion!=0){
     page_counter= page_counter +1;
     }
  }
  if (enter.check() == LOW) {
    Serial.println(F("ENTER button pressed"));
    // Switches focus to the next line.
   menu.call_function(1);
    
  }
      if (page_counter>cantidadPaginas){
        page_counter=1;
      }
      if (page_counter<1){
        page_counter=cantidadPaginas;
      }   
 }

void mostrarTemperatura(float temperatura){
   if(flag_temperatura!=0){// si no esta en modo medicion procede a mostrar los valores
   lcd.setCursor(0,0);
   lcd.print("Temp:");
   lcd.setCursor(10,0);
   lcd.print(temperatura,0); lcd.print("*C");
   }
  }
///////////////////////////////////////////////////////FUNCION PARA MOSTRAR VALORES EN PANTALLA////////////////////////////////////////////////////////////////// 

void mostrarValores(float a,float b,float c,float d, float e,float f,float g,float h){

  if(flag_medicion!=0){// si no esta en modo medicion procede a mostrar los valores

  switch (page_counter){
    case 1: //Design of home page 1     
      lcd.setCursor(0,0);
      lcd.print(VARIABLE1);
      lcd.setCursor(12,0);
      lcd.print(a,0); lcd.print(UNIDAD1);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE2);
      if (b<=200){
        lcd.setCursor(12,1);
        lcd.print(int(b),1); 
        lcd.print(UNIDAD2);
      }
      else{
        lcd.print("200W"); 
      }
      delay(10);
      break;
    case 2: //Design of page 2
      lcd.setCursor(0,0);
      lcd.print(VARIABLE3);
      lcd.setCursor(12,0);
      lcd.print(c,0); lcd.print(UNIDAD3);
      lcd.setCursor(0,1);
      lcd.print(VARIABLE4); 
      lcd.setCursor(12,1);
      lcd.print(d,1); lcd.print(UNIDAD4);
      delay(10);
      break;
    case 3: //Design of page 3 
       lcd.setCursor(0,0);
      lcd.print(VARIABLE5);
      lcd.setCursor(12,0);
      lcd.print(e,0); lcd.print(UNIDAD5);
      lcd.setCursor(0,1);
      lcd.print(VARIABLE6);
      lcd.setCursor(12,1);
      lcd.print(int(f),1); lcd.print(UNIDAD6);
      delay(10);
      break;
     case 4: //Design of page 4 
        lcd.setCursor(0,0);
      lcd.print(VARIABLE7);
      lcd.setCursor(12,0);
      lcd.print(g,0); lcd.print(UNIDAD7);
      lcd.setCursor(0,1);
      lcd.print(VARIABLE8);
      lcd.setCursor(12,1);
      lcd.print(int(h),1); lcd.print(UNIDAD8);
      delay(10);
/*
      case 5: //Design of page 4 
        lcd.setCursor(0,0);
      lcd.print("Medicion1");
      lcd.setCursor(12,0);
      lcd.print(g,0); lcd.print("P");
      lcd.setCursor(0,1);
      lcd.print("Medicion2");
      lcd.setCursor(12,1);
      lcd.print(int(h),1); lcd.print("P");
      delay(10);
          case 6: //Design of page 4 
        lcd.setCursor(0,0);
      lcd.print("Medicion3");
      lcd.setCursor(12,0);
      lcd.print(g,0); lcd.print("P");
      lcd.setCursor(0,1);
      lcd.print("Medicion4");
      lcd.setCursor(12,1);
      lcd.print(int(h),1); lcd.print("P");
      delay(10);
          case 7: //Design of page 4 
        lcd.setCursor(0,0);
      lcd.print("Medicion5");
      lcd.setCursor(12,0);
      lcd.print(g,0); lcd.print("P");
      lcd.setCursor(0,1);
      lcd.print("Medicion6");
      lcd.setCursor(12,1);
      lcd.print(int(h),1); lcd.print("P");
      delay(10);
          case 8: //Design of page 4 
        lcd.setCursor(0,0);
      lcd.print("Medicion7");
      lcd.setCursor(12,0);
      lcd.print(g,0); lcd.print("P");
      lcd.setCursor(0,1);
      lcd.print("Medicion8");
      lcd.setCursor(12,1);
      lcd.print(int(h),1); lcd.print(UNIDAD8);
      delay(10);
*/
      
      break;
      default: 
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
  flag_medicion=1;
  page_counter=1; 
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

/////////////////////////////
void fn_configuracion(){
  flag_medicion=0;
  flag_temperatura=0;
  lcd.clear(); 
  menu.change_screen(2);
  menu.set_focusedLine(0);
  
}
/////////////////////////////
void fn_mas_configuraciones(){
  menu.change_screen(3);
  menu.set_focusedLine(0);
}

void fn_temperatura(){
  flag_temperatura=1;
  menu.change_screen(4);
  menu.set_focusedLine(0);
}


 
