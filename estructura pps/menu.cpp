
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



float aux = 0.0; //Definimos la variable auxiliar
  int i=0;
  float lectura[5]  ;//Definimos la variable value

   for(i=0;i<6;i++)
  {
       lectura[i]= readyprom(i);
  
  }


void mostrarValores(){
 switch (page_counter) {
   
    case 1:{     //Design of home page 1
      
      lcd.setCursor(0,0);
      lcd.print("Isal:"); lcd.print(corriente,0); lcd.print("A");
   
      lcd.setCursor(9,0);
        
      lcd.print("Pd:");
      if (potenciad<=200)
      {
      lcd.print(potenciad,0); 
      lcd.print("W");
      }
      else
      lcd.print("200W"); 
      
      lcd.setCursor(0,1);
      lcd.print("Vex:"); lcd.print(vex,0); lcd.print("V");
      
      lcd.setCursor(9,1);
      lcd.print("AG:"); lcd.print(agc,1); lcd.print("V");
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
  Valores();
  lcd.clear();  
  menu.change_screen(2);
  menu.set_focusedLine(0);
}
void fn_led2(){
  menu.change_screen(3);
  menu.set_focusedLine(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrarValores(){
 switch (page_counter) {
   
    case 1:{     //Design of home page 1
      
      lcd.setCursor(0,0);
      lcd.print("Isal:"); lcd.print(corriente,0); lcd.print("A");
   
      lcd.setCursor(9,0);
        
      lcd.print("Pd:");
      if (potenciad<=200)
      {
      lcd.print(potenciad,0); 
      lcd.print("W");
      }
      else
      lcd.print("200W"); 
      
      lcd.setCursor(0,1);
      lcd.print("Vex:"); lcd.print(vex,0); lcd.print("V");
      
      lcd.setCursor(9,1);
      lcd.print("AG:"); lcd.print(agc,1); lcd.print("V");
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
  
 
