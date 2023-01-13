//////////////////////// VALORESS DE MEDICION A MOSTRAR EN PANTALLA /////////////////////////////////
volatile int interruptCounter;
bool flagValores=false;
bool flagADC=false;
///////////////////////////////////////////
float valorPD= 500;
float valorPR= 200;
float valorAGC= 20;
float valorIsal= 8.8;
float valorVsal= 48;
float valorVexc= 28;
float valorVaux= 12;
float valorVlinea= 220; 
float bitsResolucion=12;//4096 valores
/////////////////////////////////////////
float Escala1=0;
float Escala2=0;
float Escala3=0;
float Escala4=0;
float Escala5=0;
float Escala6=0;
float Escala7=0;
float Escala8=0;
float Promedio[8]={8,8,8,8,8,8,8,8};
////////////////////////////////////////////
String VARIABLE1="PD_ANTE: ";
String VARIABLE2="PR_ANTE: ";
String VARIABLE3="%_AUDIO: ";
String VARIABLE4="I_SAL: ";
String VARIABLE5="V_SAL: ";
String VARIABLE6="V_EXC: ";
String VARIABLE7="V_AUX: ";
String VARIABLE8="V_LINEA: ";
String TIPOEQUIPO="M500W";
/////////////////////////////////////////
String UNIDAD1="Wav";
String UNIDAD2="Wav";
String UNIDAD3="%";
String UNIDAD4="A";
String UNIDAD5="Vcc";
String UNIDAD6="Vcc";
String UNIDAD7="Vcc";
String UNIDAD8="Vca";
