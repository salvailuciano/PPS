#include "DHT.h"
#include "temperatura.h"
#include "definesConfiguraciones.h"

//#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
#define DHTTYPE DHT22   // Sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup_temperatura() {
  dht.begin();
}
long tiempoUltimaLectura=0;; //Para guardar el tiempo de la última lectura
int lecturaTemperatura() {
      
      float h = dht.readHumidity(); //Leemos la Humedad
      float temperatura = dht.readTemperature(); //Leemos la temperatura en grados Celsius
      //float f = dht.readTemperature(true); //Leemos la temperatura en grados Fahrenheit
      //--------Enviamos las lecturas por el puerto serial-------------
   /*
      Serial.print("Humedad ");
      Serial.print(h);
      Serial.print(" %t");
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.print(" *C ");
      */
    //  Serial.print(f);
     // Serial.println(" *F");
     // tiempoUltimaLectura=millis(); //actualizamos el tiempo de la última lectura
     return temperatura;
  delay(100);
}
