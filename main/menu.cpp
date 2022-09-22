#include <Arduino.h>
#include "menu.h"
#include "Button.h"
#include "eeprom.h"
#include "definesConfiguraciones.h"
#include <LiquidMenu.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); //Descomentar si se usa I2C

//void setup_numerosgrandes();
//void printNumerosgrandes(int numero);

// the 8 arrays that form each segment of the custom numbers
byte bar1[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};
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

int flag_medicion=1 ;       //Variable que indica si esta en modo medicion o configuracion
int flag_temperatura=0 ;       //Variable que indica si esta en modo medicion o configuracion
int flag_config_cal=0;
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
LiquidLine analog_line1_2(1, 0, VARIABLE1, analogValue[0]);
LiquidLine analog_line2_2(1, 0, VARIABLE2, analogValue[1]);
LiquidLine analog_line3_2(1, 0, VARIABLE3, analogValue[2]);
LiquidLine analog_line4_2(1, 0, VARIABLE4, analogValue[3]);
LiquidScreen pantalla2(analog_line1_2,analog_line2_2,analog_line3_2,analog_line4_2);
*/
LiquidLine linea1_3(0, 0," ");
LiquidLine linea2_3(1, 1);
LiquidScreen pantalla3(linea1_3,linea2_3);

LiquidLine linea1_4(1, 0);
LiquidScreen pantalla4(linea1_4);

LiquidMenu menu(lcd,pantalla2,pantalla1,pantalla3,pantalla4);
//////////////////////////////////////FUNCIONES LIGADAS AL MENU//////////////////////////////////////////////////
void setup_menu(){
  setup_numerosgrandes();
  //lcd.init(); //Descomentar para I2C
//lcd.begin(16, 2); //Comentar si se usa I2C
  //lcd.backlight(); // Descomentar para I2C
//Primero se inicializa en que posicion estara el cursor RIGHT o LEFT
  menu.init();
  linea1.set_focusPosition(Position::LEFT); 
  linea2.set_focusPosition(Position::LEFT); 
  linea3.set_focusPosition(Position::LEFT); 
  linea4.set_focusPosition(Position::LEFT); 
//Se indexan las funciones que se ejecutaran en cada linea   
  linea1.attach_function(1,fn_mediciones); 
  linea2.attach_function(1,fn_configuraciones_calibraciones); 
  linea3.attach_function(1,fn_configuraciones_calibraciones); 
  linea4.attach_function(1,fn_temperatura); 
//Se añade esta pantalla
  menu.add_screen(pantalla1);

  linea1_2.set_focusPosition(Position::LEFT); 
  linea2_2.set_focusPosition(Position::LEFT); 
  linea3_2.set_focusPosition(Position::LEFT); 
  linea4_2.set_focusPosition(Position::LEFT); 
  
  linea1_2.attach_function(1, fn_configuracion);
  linea2_2.attach_function(1, fn_configuracion);
  linea3_2.attach_function(1, fn_configuracion); 
  linea4_2.attach_function(1, fn_configuracion);
  menu.add_screen(pantalla2);

  linea1_3.set_focusPosition(Position::LEFT);
  linea2_3.set_focusPosition(Position::LEFT); 
  
  linea2_3.attach_function(1, fn_configuracion);
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
  }*/
  
  if (up.check() == LOW) {
    Serial.println(F("UP button pressed"));
    // Calls the function identified with one
    // for the focused line.
    menu.switch_focus(false);
    //Si el flag de medicion es distinto a cero aumenta el page counter para movilizar el cursor
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

void mostrarCalibraciones(float variable1,float variable2,float variable3,float variable4,float variable5,float variable6,float variable7,float variable8){
   if(flag_config_cal!=0){// si no esta en modo medicion procede a mostrar los valores
  switch (contador_ajuste){
    case 0: //Ajuste medicion1 
      
      lcd.setCursor(0,0);
      lcd.print(VARIABLE1);
      lcd.setCursor(12,0);
      lcd.print(variable1,0); lcd.print(UNIDAD1);//MUESTRA VALOR A CALIBRAR Y SU UNIDAD
      lcd.setCursor(1,1);
      lcd.print("Atras");//MUESTRA BOTON ATRAS POR SI NO SE QUIERE CALIBRAR ESA MEDICION
      if (up.check() == LOW) {
      variable1++;
      }
       if (down.check() == LOW) {
      variable1--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;
      
      case 1: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE2);
      lcd.setCursor(12,0);
      lcd.print(variable2,0); lcd.print(UNIDAD2);
      lcd.setCursor(1,1);
      lcd.print("Atras");
      if (up.check() == LOW) {
      variable2++;
      }
       if (down.check() == LOW) {
      variable2--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;

      case 2: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE3);
      lcd.setCursor(12,0);
      lcd.print(variable3,0); lcd.print(UNIDAD3);
      lcd.setCursor(1,1);
      lcd.print("Atras");
      if (up.check() == LOW) {
      variable3++;
      }
       if (down.check() == LOW) {
      variable3--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;
      
      case 3: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE4);
      lcd.setCursor(12,0);
      lcd.print(variable4,0); lcd.print(UNIDAD4);
      lcd.setCursor(1,1);
      lcd.print("Atras");
      if (up.check() == LOW) {
      variable4++;
      }
       if (down.check() == LOW) {
      variable4--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;
      break;
      case 4: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE5);
      lcd.setCursor(12,0);
      lcd.print(variable5,0); lcd.print(UNIDAD5);
      lcd.setCursor(1,1);
      lcd.print("Atras");
      if (up.check() == LOW) {
      variable5++;
      }
       if (down.check() == LOW) {
      variable5--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;
      case 5: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE6);
      lcd.setCursor(12,0);
      lcd.print(variable6,0); lcd.print(UNIDAD6);
      lcd.setCursor(1,1);
      lcd.print("Atras");
      if (up.check() == LOW) {
      variable6++;
      }
       if (down.check() == LOW) {
      variable6--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;
      case 6: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE7);
      lcd.setCursor(12,0);
      lcd.print(variable7,0); lcd.print(UNIDAD7);
      lcd.setCursor(1,1);
      lcd.print("Atras");
      if (up.check() == LOW) {
      variable7++;
      }
       if (down.check() == LOW) {
      variable7--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;

      case 7: //Ajuste medicion1 
      lcd.setCursor(0,0);
      lcd.print(VARIABLE8);
      lcd.setCursor(12,0);
      lcd.print(variable8,0); lcd.print(UNIDAD8);
      lcd.setCursor(1,1);
      lcd.print("Atras");
      if (up.check() == LOW) {
      variable8++;
      }
       if (down.check() == LOW) {
      variable8--;
      }
        if (enter.check() == LOW) {
      contador_ajuste++;
      }
      delay(10);
      break;
   }
  }
  writeEEPROM(variable1,variable2,variable3,variable4,variable5,variable6,variable7,variable8);//guardar los nuevos valores en la EEPROM
 } 
///////////////////////////////////////////////////////FUNCION PARA MOSTRAR VALORES EN PANTALLA////////////////////////////////////////////////////////////////// 

void mostrarValores(float a,float b,float c,float d, float e,float f,float g,float h){

  if(flag_medicion!=0){// si no esta en modo medicion procede a mostrar los valores

  switch (page_counter){
    case 1: //Design of home page 1     
      lcd.setCursor(0,0);
      lcd.print(VARIABLE1);
      lcd.setCursor(12,0);
      printNumerosgrandes(a);
      //lcd.print(a,0); lcd.print(UNIDAD1);
      
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

////////////////////////////////////////////////////FUNCIONES DEL MENU//////////////////////////////////////////////////////////////////////
/*void selectOption(){
  if(enter.check() == LOW){
    lcd.clear(); 
    menu.call_function(1);
   // delay(500);
  }
}*/
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
////////////////////////////////////////////FUNCION PARA MOSTRAR NUMEROS GRANDES//////////////////////////////////////////////////////////
void setup_numerosgrandes(){
    lcd.init(); //Descomentar para I2C
//lcd.begin(16, 2); //Comentar si se usa I2C
  lcd.backlight(); // Descomentar para I2C
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





 
