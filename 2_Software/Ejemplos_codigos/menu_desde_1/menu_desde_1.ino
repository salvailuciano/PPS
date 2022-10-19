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

  value = analogRead(analogInput); //Leemos el pin analógico A0
   vout = (value * 5.0) / 1024.0; // Cálculo para obtener el Vout //Valor * voltaje/BitsADC
   vin = vout / (R2/(R1+R2)); // Cálculo para obtener Vin del divisor de tensión
   
   if (vin<0.09) 
   {
    //Si la lectura de Vin es menor que 0.09V le decimos que nos muestre 0
   vin=0.0;
   }

  
  selectOption();

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
