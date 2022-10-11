#include <Arduino.h>
#include "menu.h"
#include "Button.h"
#include "numeros_grandes.h"
#include "eeprom.h"
#include "definesConfiguraciones.h"
#include "serial.h"

//#include <LiquidCrystal.h> // Funcion para coneccion de LCD por piner de Datos

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

int flag_medicion=1 ;       //Variable que indica si esta en modo medicion o configuracion
int flag_temperatura=0 ;       //Variable que indica si esta en modo medicion o configuracion
int flag_config_cal=0;
int flag_config_cal_serial=0;
int page_counter=1 ;       //To move beetwen pages
int cantidadPaginas=4;
int contador_ajuste=0;

///////////////////////////DECLARACION DE BOTONES//////////////////////////////////
// Button objects instantiatio
const bool pullup = true;
//Button left(12, pullup);
//Button right(11, pullup);
Button up(Bot_up, pullup);
Button down(Bot_down, pullup);
Button enter(Bot_enter, pullup);

//////////////////////////////////////////////MENUES Y CONTENIDO//////////////////////////////////////////////////
//Se inicializa y se desarrolla lo que mostrara cada linea del display
LiquidLine linea1(1, 0, "Mediciones");
LiquidLine linea2(1, 1, "Calibracion");
LiquidLine linea3(1, 2, "Serial");
LiquidLine linea4(1, 3, "Temperatura");
LiquidScreen pantalla1(linea1,linea2,linea3,linea4);

LiquidLine linea1_2(1, 0);
LiquidScreen pantalla2(linea1_2);
/*
LiquidLine analog_line1_2(1, 0, VARIABLE1, analogValue[0]);
LiquidLine analog_line2_2(1, 0, VARIABLE2, analogValue[1]);
LiquidLine analog_line3_2(1, 0, VARIABLE3, analogValue[2]);
LiquidLine analog_line4_2(1, 0, VARIABLE4, analogValue[3]);
LiquidScreen pantalla2(analog_line1_2,analog_line2_2,analog_line3_2,analog_line4_2);
*/
LiquidLine linea1_3(1, 1);
LiquidScreen pantalla3(linea1_3);

LiquidLine linea1_4(1, 0);
LiquidScreen pantalla4(linea1_4);

LiquidMenu menu(lcd,pantalla2,pantalla1,pantalla3,pantalla4);
//////////////////////////////////////FUNCIONES LIGADAS AL MENU//////////////////////////////////////////////////
void setup_menu(){
  lcd.init(); //Descomentar para I2C
//lcd.begin(16, 2); //Comentar si se usa I2C
  lcd.backlight(); // Descomentar para I2C
  setup_numerosgrandes();
//Primero se inicializa en que posicion estara el cursor RIGHT o LEFT
  menu.init();
  linea1.set_focusPosition(Position::LEFT); 
  linea2.set_focusPosition(Position::LEFT); 
  linea3.set_focusPosition(Position::LEFT); 
  linea4.set_focusPosition(Position::LEFT); 
//Se indexan las funciones que se ejecutaran en cada linea   
  linea1.attach_function(1,fn_mediciones); 
  linea2.attach_function(1,fn_configuraciones_calibraciones); 
  linea3.attach_function(1,fn_configuraciones_serial); 
  linea4.attach_function(1,fn_temperatura); 
//Se añade esta pantalla
  menu.add_screen(pantalla1);

  linea1_2.set_focusPosition(Position::LEFT); 
  linea1_2.attach_function(1, fn_configuracion);
  menu.add_screen(pantalla2);

  linea1_3.set_focusPosition(Position::LEFT);
  linea1_3.attach_function(1, fn_configuracion);
  menu.add_screen(pantalla3);

  linea1_4.set_focusPosition(Position::LEFT); 
  linea1_4.attach_function(1, fn_configuracion);
  menu.add_screen(pantalla4);
//Se establece cuantas lineas tendra el display en pantalla
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
  }
  */

  
  
  if (up.check() == LOW) {
   // Serial.println(F("UP button pressed"));
    // Calls the function identified with one
    // for the focused line.
     if(flag_config_cal==0){
    menu.switch_focus(false);
     }
    //Si el flag de medicion es distinto a cero aumenta el page counter para movilizar el cursor
    if(flag_medicion!=0){
    page_counter= page_counter -1;
    }
  }
  if (down.check() == LOW) {
    //Serial.println(F("DOWN button pressed"));
    if(flag_config_cal==0){
     menu.switch_focus(true);
    }
    if(flag_medicion!=0){
     page_counter= page_counter +1;
     }
  }
  if (enter.check() == LOW) {
    //Serial.println(F("ENTER button pressed"));
    // Switches focus to the next line.
    if(flag_config_cal==0){
    menu.call_function(1);
     }
     else {
      lcd.clear();
      contador_ajuste++;
      }
  }
      if (page_counter>cantidadPaginas){
        page_counter=1;
      }
      if (page_counter<1){
        page_counter=cantidadPaginas;
      }   
 }

//////////////////////////////////////FUNCION PARA MOSTRAR LA TEMPERATURA EN PANTALLA////////////////////////////////////////////////////////////////
void mostrarTemperatura(float temperatura){
   if(flag_temperatura!=0){// si no esta en modo medicion procede a mostrar los valores
   lcd.setCursor(0,0);
   lcd.print("Temp:");
   lcd.setCursor(10,0);
   lcd.print(temperatura,0); lcd.print("*C");
   }
  }


//////////////////////////////////////FUNCION PARA CALIBRAR LOS VALORES MOSTRADOS EN PANTALLA////////////////////////////////////////////////////////////////
//Esta funcion es de simple calibracion para las mediciones que se quieren ver en pantalla
//Los pasos a seguir son:
//1)En cada caso se mostrara la medicion
//2)Se ajustara el valor de la medicion con botup y botdown
//3)Con el enter se pasará a ajustar la siguiente medición
//4)Luego de pasar por todas las mediciones, se guardara la cablibracion en la EEPROM

void mostrarCalibraciones(){
   if(flag_config_cal!=0){// si no esta en modo medicion procede a mostrar los valores
  switch (contador_ajuste){

      case 0: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE1);
      lcd.setCursor(12,0);
      lcd.print(valorPD,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD1);
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW)  {
      valorPD++;
      }
       if (digitalRead(0) == LOW) {
      valorPD--;
      }
      break;
  
      case 1: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE2);
      lcd.setCursor(12,0);
      lcd.print(valorPR,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD2);
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW) {
      valorPR++;
      }
       if (digitalRead(0)  == LOW) {
      valorPR--;
       }
      break;

      case 2: //Ajuste medicion1
      lcd.setCursor(0,0);
      lcd.print(VARIABLE3);
      lcd.setCursor(12,0);
      lcd.print(valorAGC,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD3);
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW) {
      valorAGC++;
      }
        if (digitalRead(0)  == LOW) {
      valorAGC--;
       }
      break;

      case 3: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE4);
      lcd.setCursor(12,0);
      lcd.print(valorIsal,1);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD4);
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW) {
      valorIsal+=0.1;
      }
       if (digitalRead(0)  == LOW) {
      valorIsal-=0.1;
       }
      break;
  
      case 4: //Ajuste medicion1
      lcd.setCursor(0,0);
      lcd.print(VARIABLE5);
      lcd.setCursor(12,0);
      lcd.print(valorVsal,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD5);
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW) {
      valorVsal++;
      }
       if (digitalRead(0)  == LOW) {
      valorVsal--;
       }
      break;

      case 5: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE6);
      lcd.setCursor(12,0);
      lcd.print(valorVexc,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD6); 
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW) {
      valorVexc++;
      }
       if (digitalRead(0)  == LOW) {
      valorVexc--;
       }
      break;

      case 6: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE7);
      lcd.setCursor(12,0);
      lcd.print(valorVaux,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD7);
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW) {
      valorVaux++;
      }
      if (digitalRead(0)  == LOW) {
      valorVaux--;
       }
      break;
     
      case 7: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE8);
      lcd.setCursor(12,0);
      lcd.print(valorVlinea,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD8);
      lcd.setCursor(1,1);
      lcd.print("Siguiente");
      if (digitalRead(5) == LOW) {
      valorVlinea++;
      }
      if (digitalRead(0)  == LOW) {
      valorVlinea--;
       }
      break;

      case 8: //Ajuste medicion1 
      writeEEPROM(valorPD,valorPR,valorAGC,valorIsal,valorVsal,valorVexc,valorVaux,valorVlinea);
      contador_ajuste=0;
      menu.call_function(1);
      break;
   }
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
      lcd.print(a,0); 
      lcd.setCursor(15,0);
      lcd.print(UNIDAD1);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE2);
      if (b<=500){
        lcd.setCursor(12,1);
        lcd.print(int(b),1); 
        lcd.setCursor(15,1);
        lcd.print(UNIDAD2);
      }
      else{
        lcd.setCursor(12,1);
        lcd.print("500W"); 
      }
      delay(100);
      
      break;
    case 2: //Design of page 2
      lcd.setCursor(0,0);
      lcd.print(VARIABLE3);
      lcd.setCursor(12,0);
      lcd.print(c,0); 
      lcd.setCursor(15,0);
      lcd.print(UNIDAD3);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE4); 
      lcd.setCursor(12,1);
      lcd.print(d,1);
      lcd.setCursor(15,1);
      lcd.print(UNIDAD4);
      
      delay(100);
      break;
    case 3: //Design of page 3 
       lcd.setCursor(0,0);
      lcd.print(VARIABLE5);
      lcd.setCursor(12,0);
      lcd.print(e,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD5);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE6);
      lcd.setCursor(12,1);
      lcd.print(int(f),1);
      lcd.setCursor(15,1);
      lcd.print(UNIDAD6);
      delay(100);
      break;
     case 4: //Design of page 4 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE7);
      lcd.setCursor(12,0);
      lcd.print(g,0);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD7);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE8);
      lcd.setCursor(12,1);
      lcd.print(int(h),1);
      lcd.setCursor(15,1);
      lcd.print(UNIDAD8);
      delay(100); 
      break;
      
      default: 
      break;
    }
  }
}

void mostrarcalibracionSerial(){
     bool menuConfiguracion=0;
     if(flag_config_cal_serial!=0)
      {
      lcd.setCursor(0,0);
      lcd.print("Modo");
      lcd.setCursor(0,1);
      lcd.print("Serial");
      menuConfiguracion=calibracionesGenerales();
      if (menuConfiguracion==1){
        lcd.clear(); 
        ESP.restart();
        }
      }
}
////////////////////////////////////////////////////FUNCIONES DEL MENU//////////////////////////////////////////////////////////////////////

///////////////////////////////////////FUNCION PARA MOSTRAR LAS MEDICIONES EN PANTALLA//////////////////////////////////////////////////////
void fn_mediciones(){
  lcd.clear(); 
  flag_medicion=1;
  page_counter=1; 
  menu.change_screen(1);
  menu.set_focusedLine(0);
  }

///////////////////////////////////////////////FUNCION PARA MOSTRAR LAS CONFIGURACIONES/////////////////////////////////////////////////////
void fn_configuracion(){
  flag_medicion=0;
  flag_temperatura=0;
  flag_config_cal=0;
  flag_config_cal_serial=0;
  lcd.clear(); 
  menu.change_screen(2);
  menu.set_focusedLine(0);
  }
//////////////////////////////////////////////FUNCION PARA MOSTRAR LA TEMPERATURA MEDIDA////////////////////////////////////////////////////
void fn_temperatura(){
  flag_temperatura=1;
  menu.change_screen(4);
  menu.set_focusedLine(0);
  }
/////////////////////////////FUNCION PARA CALIBRAR LAS MEDICIONES MOSTRADAS EN PANTALLA////////////////////////////////////////////////////
void fn_configuraciones_calibraciones(){
   flag_config_cal=1;
   menu.change_screen(3);
   menu.set_focusedLine(0);
  }

void fn_configuraciones_serial(){
  menu.change_screen(3);
  menu.set_focusedLine(0);
  flag_config_cal_serial=1;
  }

////////////////////////////////////////////FUNCION PARA MOSTRAR NUMEROS GRANDES//////////////////////////////////////////////////////////
void setup_numerosgrandes(){
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);
  }

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void printNumero(int valor, int col) {
  if (valor == 0) {
    custom0(col);
  } if (valor == 1) {
    custom1(col);
  } if (valor == 2) {
    custom2(col);
  } if (valor == 3) {
    custom3(col);
  } if (valor == 4) {
    custom4(col);
  } if (valor == 5) {
    custom5(col);
  } if (valor == 6) {
    custom6(col);
  } if (valor == 7) {
    custom7(col);
  } if (valor == 8) {
    custom8(col);
  } if (valor == 9) {
    custom9(col);
  }      
}  

void printNumerosgrandes(int numero) {
  int milena , centena, decena, unidad;
  /*
  if (number > 999) {
    milena = (numero - (numero % 1000)) / 1000;
    numero = numero % 1000;
  } else {
    milena = 0;
  }  
  */
  if (numero > 99) {
    centena = (numero - (numero % 100)) / 100;
    numero = numero % 100;
  } else {
    centena = 0;
  }  

  if (numero > 9) {
    decena = (numero - (numero % 10)) / 10;
    numero = numero % 10;
  } else {
    decena = 0;
  }  
  unidad = numero;

 // printNumero(milena, 4);
  printNumero(centena, 7);
  printNumero(decena, 10);
  printNumero(unidad, 13);
}  





 
