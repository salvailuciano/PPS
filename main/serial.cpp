//#include <Preferences.h>
/*
String VARIABLE1="P Directa: ";
String VARIABLE2="P Refejada: ";
String VARIABLE3="AGC: ";
String VARIABLE4="I Salida: ";
String VARIABLE5="V Salida: ";
String VARIABLE6="Vexc: ";
String VARIABLE7="Vaux: ";
String VARIABLE8="V linea: ";
String TIPOEQUIPO="M500W";
//String  command;
bool userInput = false;

void waitForUserInput();
void resetInput();

Preferences preferences;

void setup()
{
    Serial.begin(115200);
    Serial.println();
    
    Serial.println("Desea Ingresar y/o cambiar de credenciales WiFi? (S/N)");        
    
    waitForUserInput();    
    command.toLowerCase();
    command.trim();
    Serial.println(command);
    //
    if (command.equals("s")){
        resetInput();

        Serial.println("Ingrese el Identificador de la red:");
        waitForUserInput();
        command.trim();
        Serial.println(command);
        ssid = command;
        resetInput();

        Serial.println("Ingrese la Contrasena de la red:");
        waitForUserInput();
        command.trim();
        Serial.println(command);
        password = command;
        resetInput();

        // Guardar/reemplazar namespace
        preferences.begin("credenciales", false);
        preferences.putString("ssid", ssid);
        preferences.putString("password", password);
        preferences.end();
        Serial.println("Se guardaron las Credenciales\n.");          
    }

    // Intentar conectarse a la red
    delay(1000);    
    tryLoadAndConnectToWiFi();
    
} // eof setup

void loop()
{
    // SU CODIGO A IMPLEMENTAR
}


void waitForUserInput()
{
    while (!userInput)
    {
        if (Serial.available() > 0)
        {
            char c = (char)Serial.read();
            if (c != '\n')
            {
                command += c;
            }
            else
            {
                userInput = true;
                return;
            }
        }
    }
}


void resetInput(){
    userInput = false;
    command = "";
}
*/
