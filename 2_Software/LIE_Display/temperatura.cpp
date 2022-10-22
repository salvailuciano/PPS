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
     return temperatura;
  delay(100);
}
