#include <LiquidCrystal_I2C.h> //Descomentar para I2C
#include <LiquidMenu.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); //Descomentar si se usa I2C

//#include <LiquidCrystal.h> // Funcion para coneccion de LCD por piner de Datos

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
