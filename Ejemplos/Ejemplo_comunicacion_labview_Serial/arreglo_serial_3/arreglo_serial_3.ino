#define DEBUG(a) Serial.println(a);
String data = "";
void setup()
{
   Serial.begin(9600);
}
void loop()
{
   while (Serial.available())
   {
      char character = Serial.read();
      if (character != '\n')
      {
         data.concat(character);
      }
      else
      {
         Serial.println(data);
         data = "";
      }
   }
}
