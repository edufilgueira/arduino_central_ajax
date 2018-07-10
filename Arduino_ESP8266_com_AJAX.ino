#include <ESP8266WiFi.h>

const char* ssid = "eduardo";
const char* password = "edumel00";

WiFiServer server(80);

#define _pino0 D0 //GPIO16
#define _pino1 D1 //GPIO5
#define _pino2 D2 //GPIO4
#define _pino3 D3 //GPIO0
#define _pino4 D4 //GPIO2
#define _pino5 D5 //GPIO14
#define _pino6 D6 //GPIO12
#define _pino7 D7 //GPIO13
#define _pino8 D8 //GPIO15


void setup()
{
    Serial.begin(115200);

    //Conexão na rede WiFi
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi conectado!");

    // Inicia o servidor WEB
    server.begin();
    Serial.println("Server iniciado");

    // Mostra o endereco IP
    Serial.println(WiFi.localIP());
  
    pinMode(_pino0, OUTPUT);
    pinMode(_pino1, OUTPUT);
    pinMode(_pino2, OUTPUT);
    pinMode(_pino3, OUTPUT);
    pinMode(_pino4, OUTPUT);
    pinMode(_pino5, OUTPUT);
    pinMode(_pino6, OUTPUT);
    pinMode(_pino7, OUTPUT);
    pinMode(_pino8, OUTPUT);
  
    digitalWrite(_pino0, LOW);
    digitalWrite(_pino1, LOW);
    digitalWrite(_pino2, LOW);
    digitalWrite(_pino3, LOW);
    digitalWrite(_pino4, LOW);
    digitalWrite(_pino5, LOW);
    digitalWrite(_pino6, LOW);
    digitalWrite(_pino7, LOW);
    digitalWrite(_pino8, LOW);
}

String HTTP_req; 
String URLValue;

void loop()
{

    WiFiClient  client = server.available();

    if (client) {
 
        boolean continua = true;
	String linha = "";        

	while (client.connected()) {
            if (client.available()) { 
                char c = client.read(); 
                linha.concat(c); 
                client.println("url: "+c);

                if (c == '\n' && continua )
		{ 

 		}
                if (c == '\n') { continua = true; } 
                else if (c != '\r') { continua = false; }
            }
        } 
        delay(1);     
        client.stop(); 
    } 
}


