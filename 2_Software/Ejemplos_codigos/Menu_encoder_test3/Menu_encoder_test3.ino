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


int page_counter=1 ;       //To move beetwen pages


void setup() {

  
  pinMode(sw,INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  

}

void loop() {


   value = analogRead(analogInput); //Leemos el pin analógico A0
   vout = (value * 5.0) / 1024.0; // Cálculo para obtener el Vout //Valor * voltaje/BitsADC
   vin = vout / (R2/(R1+R2)); // Cálculo para obtener Vin del divisor de tensión
   
   if (vin<0.09) 
   {
    //Si la lectura de Vin es menor que 0.09V le decimos que nos muestre 0
   vin=0.0;
   }


  aState = digitalRead(outputA); 
    if (aState != aLastState){    
      lcd.clear();  
      if (digitalRead(outputB) != aState) { 
       page_counter= page_counter -1; 
      } else {
        page_counter= page_counter +1;
      }
      if (page_counter>3) page_counter=1;
      if (page_counter<1) page_counter=3;
      aLastState = aState;
  }

    switch (page_counter) {
   
    case 1:{     //Design of home page 1
      
      lcd.setCursor(0,0);
      lcd.print(vin); lcd.print(" V");
      corriente = 2;
      lcd.setCursor(9,0);
      lcd.print(corriente); lcd.print(" A");
      potencia = voltaje * corriente ;
      lcd.setCursor(0,1);
      lcd.print(potencia); lcd.print(" W");
      energia = energia + (potencia / 3600);
      lcd.setCursor(9,1);
      lcd.print(energia); lcd.print(" Wh");
    }
    break;

    case 2: { //Design of page 2 
     lcd.setCursor(5,0);
     lcd.print("This is");
     lcd.setCursor(5,1);
     lcd.print("Page 2");
    }
    break;

    case 3: {   //Design of page 3 
     lcd.setCursor(1,0);
     lcd.print("You are now on");
     lcd.setCursor(4,1);
     lcd.print("Page 3");
    }
    break;
    
  }//switch end
  

  

}
