

#include <Preferences.h>
#include <WiFi.h>

String ssid;
String password;

String command;
bool userInput = false;

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

void tryLoadAndConnectToWiFi()
{
    preferences.begin("credenciales", false);
    ssid = preferences.getString("ssid", "");
    password = preferences.getString("password", "");
    preferences.end();

    if (ssid == "" || password == "")
    {
        Serial.println("No existen Credenciales WiFi guardadas!");
    }
    else
    {
        // Conectarse
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid.c_str(), password.c_str());
        Serial.print("Credenciales cargadas de memoria!\nConectando al WiFi ...");
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print('.');
            delay(1000);
        }
        Serial.println();
        Serial.println(WiFi.localIP());      
    }
}
