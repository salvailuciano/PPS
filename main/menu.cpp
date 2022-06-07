#include <Arduino.h>
#include "menu.h"
#include "definesConfiguraciones.h"
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>


LiquidCrystal_I2C lcd(0x3f, 16, 2);

//ENCODER
#define outputA 3
#define outputB 4
#define sw 8

int stateA=0,stateB=0;// para el encoder
int page_counter ;       //To move beetwen pages

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


void setup_menu(){
  
  lcd.init();
//lcd.begin();
  lcd.backlight();
  pinMode(sw,INPUT_PULLUP);
  
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

void encoder(int pagina)
{
  stateA = digitalRead(outputA); 
    if (stateA != stateB){     
      if (digitalRead(outputB) != stateA) { 

        menu.switch_focus(true);
      } else {
   
        menu.switch_focus(false);
      }
      if(page_counter!=0)
      {
       if (digitalRead(outputB) != stateA) { 
       page_counter= page_counter -1; 
      } else {
        page_counter= page_counter +1;
      }
      if (page_counter>3) page_counter=1;
      if (page_counter<1) page_counter=3;
      }
      menu.update();
      stateB = stateA;
  }  
  pagina = page_counter;
  }


void mostrarValores(float a,float b,float c,float d){
 switch (page_counter) {
   
    case 1:{     //Design of home page 1
      
      lcd.setCursor(0,0);
      lcd.print("Isal:"); lcd.print(a,0); lcd.print("A");
   
      lcd.setCursor(9,0);
        
      lcd.print("Pd:");
      if (b<=200)
      {
      lcd.print(b,0); 
      lcd.print("W");
      }
      else
      lcd.print("200W"); 
      
      lcd.setCursor(0,1);
      lcd.print("Vex:"); lcd.print(c,0); lcd.print("V");
      
      lcd.setCursor(9,1);
      lcd.print("AG:"); lcd.print(d,1); lcd.print("V");
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

  
  ///////////////////////////////////////////////////////FUNCIONES//////////////////////////////////////////////////////////////////

//Funciones:::::
void selectOption(){
  if(digitalRead(sw) == LOW){
     lcd.clear(); 
      menu.call_function(1);
      delay(500);
  }
}

  void fn_atras(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
  page_counter=0;
}


void fn_led1(){
   
  page_counter = 1;
  lcd.clear();  
  menu.change_screen(2);
  menu.set_focusedLine(0);
}
void fn_led2(){
  menu.change_screen(3);
  menu.set_focusedLine(0);
}

 
