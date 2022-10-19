String vectorCaracteres;
boolean TransmisionCompleta = false;

void setup() {


  Serial.begin(9600);


}

void loop() {

  //Ciclo infinito
  if (TransmisionCompleta) {
    //vectorCaracteres //Los datos ingresados se encuentran en esta variable
    vectorCaracteres = "";  //Limpiar el String
    TransmisionCompleta = false;  //Limpiar la bandera
  }
}

void serialEvent() {
  while (Serial.available()) {

    char CharEntrada = Serial.read(); //Leer un byte del puerto serial

    vectorCaracteres += CharEntrada;  //Agregar el char anterior al string

    if (CharEntrada == '\n') {  //Si se detecta un fin de linea
      TransmisionCompleta = true;  //Se indica al programa que el usuario termino de ingresar la informacion
    }
  }
}
