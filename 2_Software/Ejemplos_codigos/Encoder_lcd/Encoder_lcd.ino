#include <LiquidCrystal_I2C.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip
LiquidCrystal_I2C lcd(0x3f,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 


const int encoder_A = 2; //encoder pin A set to digital pin two as interrupt
const int encoder_B = 3; //encoder pin B set to digital pin three
const int menu = 14; //using A0 as a digital pin for a menu button
const int blue_only = 15; //using A1 as a digital pin for fluorescence viewing button
const int select = 10; //select button(encoder click) set to digital pin ten

const int menu_max[6] = {3, 2, 2, 5, 5, 1};
const int turn [4] = {0, 0, -1, 1};

byte encoder_state = 0; //tells us witch way we are going 2(10) for backwards or 3(11) for forwards
byte menu_location = 0; //tells us where we are in the menu

int encoder_position = 0; //the line of the menu that is to be selected

//menu strings
const char* main_menu = {“Select Schedule”, “Set Schedules”, “Set Time&Date”, “Set Fluorescence”};
const char* schedules_m = {“Optimal”, “Breeding”, “Custom”};
const char* seasons_m = {“With Seasons”, “Without Seasons”};
//First item in menus for printing when selected
const char* main_menu_select = {"Optimal","Optimal"};

void setup()
{
//Setting user input pins accordingly
pinMode(encoder_A,INPUT);
pinMode(encoder_B,INPUT);
pinMode(menu,INPUT);
pinMode(blue_only,INPUT);
pinMode(select,INPUT);

//Enabling internal pull up resistors
//digitalWrite(encoder_A,HIGH);
//digitalWrite(encoder_B,HIGH);
//digitalWrite(menu,HIGH);
//digitalWrite(blue_only,HIGH);
//digitalWrite(select,HIGH);

//lcd is 16X2
 lcd.init();
  lcd.backlight();
  lcd.clear();

//Setting interrupt 0(aka ecoder_A) to look for low to high and calls the encoding function
attachInterrupt(digitalPinToInterrupt(encoder_A),encoding,RISING);
}

//What happens when we use the encoder
void encoding()
{

encoder_state =0; // reset the state
encoder_state = encoder_state + digitalRead(encoder_A); // add the state of encoder_A
encoder_state <<= 1; // makes room for encoder_B
encoder_state = encoder_state + digitalRead(encoder_B); // add the state of encoder_B

encoder_position = encoder_position + turn[encoder_state];
if(encoder_position < 0)
{
encoder_position = menu_max[menu_location];
}
if(encoder_position > menu_max[menu_location])
{
encoder_position = 0;
}

switch(menu_location)
{
case 0:
lcd.clear();
lcd.print("Main Menu -4-");
lcd.setCursor(0,2);
lcd.print(main_menu[encoder_position]);
lcd.print(encoder_position);
break;

case 1:
case 2:
lcd.clear();
lcd.print(main_menu[menu_location - 1]);
lcd.setCursor(0,2);
lcd.print(schedules_m[encoder_position]);
lcd.print(encoder_position);
break;

case 3:

case 4:

case 5:
lcd.clear();
lcd.print(schedules_m[0]);
lcd.setCursor(0,2);
lcd.print(seasons_m[encoder_position]);
break;
}

return;
}

void loop()
{
if((digitalRead(select)) == LOW)
{
delay(200);

//We use a switch to advance to the correct menu depending on our current menu location
switch(menu_location)
{
case 0:
menu_location = encoder_position + 1;
lcd.clear();
lcd.print(main_menu[encoder_position]);
lcd.setCursor(0,2);
lcd.print(main_menu_select[encoder_position]);
encoder_position = 0;
break;
case 1:
break;
case 2:
menu_location += encoder_position + 3;
lcd.clear();
lcd.print("Optimal -2-");
lcd.print(menu_location);
lcd.setCursor(0,2);
lcd.print("With Seasons");
encoder_position = 0;
break;
}
}
if(((digitalRead(menu)) == LOW)&&(menu_location != 0))
{

delay(200);

//double click menu quickly or hold down to go back to main menu
for(int i = 0; i < 200; i++)
{
if((digitalRead(menu)) == LOW)
{
menu_location = 0;
}
}

//like with select a switch is used to go to the correct previous menu
switch(menu_location)
{
case 0:
case 1:
case 2:
case 3:
case 4:
menu_location = 0;
lcd.clear();
lcd.print("Main Menu -4-");
lcd.setCursor(0,2);
lcd.print(main_menu[encoder_position]);
break;

}
}

}
