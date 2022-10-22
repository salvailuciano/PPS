#include <Arduino.h>
#include "menu.h"
#include "Button.h"
#include "lcd1602Configuracion.h"
#include "eeprom.h"
#include "definesConfiguraciones.h"
#include "serial.h"

bool flag_medicion=1 ;       //Variable que indica si esta en modo medicion o configuracion
bool flag_temperatura=0 ;       //Variable que indica si esta en modo medicion o configuracion
bool flag_config_cal=0;
bool flag_config_cal_serial=0;
short page_counter=1 ;       //To move beetwen pages
short cantidadPaginas=4;
int contador_ajuste=0;

///////////////////////////DECLARACION DE BOTONES//////////////////////////////////
// Button objects instantiatio
const bool pullup = true;
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
LiquidLine linea1_3(1, 1);
LiquidScreen pantalla3(linea1_3);

LiquidLine linea1_4(1, 0);
LiquidScreen pantalla4(linea1_4);

LiquidMenu menu(lcd,pantalla2,pantalla1,pantalla3,pantalla4);
//////////////////////////////////////FUNCIONES LIGADAS AL MENU//////////////////////////////////////////////////
void setup_menu(){

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
//  Esta funcion es de simple calibracion para las mediciones que se quieren ver en pantalla
//  Los pasos a seguir son:
//  1)En cada caso se mostrara la medicion
//  2)Se ajustara el valor de la medicion con botup y botdown
//  3)Con el enter se pasará a ajustar la siguiente medición
//  4)Luego de pasar por todas las mediciones, se guardara la cablibracion en la EEPROM

void mostrarCalibraciones(){
   if(flag_config_cal!=0){// si no esta en modo medicion procede a mostrar los valores
  switch (contador_ajuste){

      case 0: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE1);
      lcd.setCursor(12,0);
      lcd.print(valorPD,0);
      if (valorPD < 100) lcd.print(" ");
      if (valorPD < 10) lcd.print(" ");
      lcd.setCursor(15,0);
      lcd.print(UNIDAD1);
      lcd.setCursor(0,1);
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
      if (valorPR < 100) lcd.print(" ");
      if (valorPR < 10) lcd.print(" ");
      lcd.setCursor(15,0);
      lcd.print(UNIDAD2);
      lcd.setCursor(0,1);
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
      if (valorAGC < 100) lcd.print(" ");
      if (valorAGC < 10) lcd.print(" ");
      lcd.setCursor(15,0);
      lcd.print(UNIDAD3);
      lcd.setCursor(0,1);
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
      lcd.setCursor(11,0);
      if (valorIsal >= 10){  
      lcd.print(valorIsal,1);
      }
      else{
      lcd.print(" ");
      lcd.print(valorIsal,1);
      }
      lcd.setCursor(15,0);
      lcd.print(UNIDAD4);
      lcd.setCursor(0,1);
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
      if (valorVsal < 100) lcd.print(" ");
      if (valorVsal < 10) lcd.print(" ");
      lcd.setCursor(15,0);
      lcd.print(UNIDAD5);
      lcd.setCursor(0,1);
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
      if (valorVexc < 100) lcd.print(" ");
      if (valorVexc < 10) lcd.print(" ");
      lcd.setCursor(15,0);
      lcd.print(UNIDAD6); 
      lcd.setCursor(0,1);
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
      if (valorVaux < 100) lcd.print(" ");
      if (valorVaux < 10) lcd.print(" ");
      lcd.setCursor(15,0);
      lcd.print(UNIDAD7);
      lcd.setCursor(0,1);
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
      if (valorVlinea < 100) lcd.print(" ");
      if (valorVlinea < 10) lcd.print(" ");
      lcd.setCursor(15,0);
      lcd.print(UNIDAD8);
      lcd.setCursor(0,1);
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

void mostrarnombreVariables(){

  if(flag_medicion!=0){// si no esta en modo medicion procede a mostrar los valores

  switch (page_counter){
    case 1: //Design of home page 1     
      lcd.setCursor(0,0);
      lcd.print(VARIABLE1);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD1);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE2);
      lcd.setCursor(15,1);
      lcd.print(UNIDAD2);
      break;
    case 2: //Design of page 2
      lcd.setCursor(0,0);
      lcd.print(VARIABLE3);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD3);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE4); 
      lcd.setCursor(15,1);
      lcd.print(UNIDAD4);
      break;
    case 3: //Design of page 3 
       lcd.setCursor(0,0);
      lcd.print(VARIABLE5);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD5);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE6);
      lcd.setCursor(15,1);
      lcd.print(UNIDAD6);
      break;
     case 4: //Design of page 4 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE7);
      lcd.setCursor(15,0);
      lcd.print(UNIDAD7);
      
      lcd.setCursor(0,1);
      lcd.print(VARIABLE8);
      lcd.setCursor(15,1);
      lcd.print(UNIDAD8); 
      break;
      
      default: 
      break;
    }
  }
}

void mostrarValores(float a,float b,float c,float d, float e,float f,float g,float h){

  if(flag_medicion!=0){// si no esta en modo medicion procede a mostrar los valores

  switch (page_counter){
    case 1: //Design of home page 1     

      lcd.setCursor(12,0);
      lcd.print(a,0); 
      if (a < 100) lcd.print(" ");
      if (a < 10) lcd.print(" ");
      
      lcd.setCursor(12,1);
      lcd.print(int(b),1); 
      if (b < 100) lcd.print(" ");
      if (b < 10) lcd.print(" ");
      break;
    case 2: //Design of page 2
      lcd.setCursor(12,0);
      lcd.print(c,0); 
      if (c < 100) lcd.print(" ");
      if (c < 10) lcd.print(" ");

      lcd.setCursor(11,1);
      if (d >= 10){  
      lcd.print(d,1);
      }
      else{
      lcd.print(" ");
      lcd.print(d,1);
      }
      break;
    case 3: //Design of page 3 
      lcd.setCursor(12,0);
      lcd.print(e,0);
      if (e < 100) lcd.print(" ");
      if (e < 10) lcd.print(" ");
      
      lcd.setCursor(12,1);
      lcd.print(int(f),1);
      if (f < 100) lcd.print(" ");
      if (f < 10) lcd.print(" ");
      break;
     case 4: //Design of page 4 
      lcd.setCursor(12,0);
      lcd.print(g,0);
      if (g < 100) lcd.print(" ");
      if (g < 10) lcd.print(" ");
      
      lcd.setCursor(12,1);
      lcd.print(int(h),1);
      if (h < 100) lcd.print(" ");
      if (h < 10) lcd.print(" ");
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




 
