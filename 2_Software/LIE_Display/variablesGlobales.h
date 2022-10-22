//////////////// VALORESS DE MEDICION A MOSTRAR EN PANTALLA //////////////////
float valorPD= 500;
float valorPR= 200;
float valorAGC= 20;
float valorIsal= 8.8;
float valorVsal= 48;
float valorVexc= 28;
float valorVaux= 12;
float valorVlinea= 220; 
float bitsResolucion=12;//1024 valores
volatile int interruptCounter;
bool flagValores=false;
bool flagADC=false;

String VARIABLE1="P Directa: ";
String VARIABLE2="P Refejada: ";
String VARIABLE3="AGC: ";
String VARIABLE4="I Salida: ";
String VARIABLE5="V Salida: ";
String VARIABLE6="Vexc: ";
String VARIABLE7="Vaux: ";
String VARIABLE8="V linea: ";
String TIPOEQUIPO="M500W";

String UNIDAD1="W";
String UNIDAD2="W";
String UNIDAD3="W";
String UNIDAD4="A";
String UNIDAD5="V";
String UNIDAD6="V";
String UNIDAD7="V";
String UNIDAD8="V";
