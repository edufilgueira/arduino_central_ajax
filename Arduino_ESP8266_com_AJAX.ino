#include <ESP8266WiFi.h>

const char* ssid = "ALCANCE TEMPLO";
const char* password = "@2018#cn";

WiFiServer server(80);

const int analogPin1 = A0;
int sensor1 = 0;
#define _pino0 16 //D0
#define _pino1 5  //D1
#define _pino2 4  //D2
#define _pino3 0  //D3
#define _pino4 2  //D4
#define _pino5 14 //D5
#define _pino6 12 //D6
#define _pino7 13 //D7
#define _pino8 15 //D8


void setup()
{
    WiFi.persistent(false);
    int counter = 0;
    while( true ) {
        WiFi.disconnect( true );
        delay(500);
        if( ++counter > 50 || WiFi.isConnected() == false ) {
          break;
        }
    }
    Serial.begin(115200);

    //Conexão na rede WiFi
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    IPAddress ip(192, 168, 0, 99); 
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config( ip, gateway,subnet );
    WiFi.reconnect();
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
  
    digitalWrite(_pino0, HIGH);
    digitalWrite(_pino1, HIGH);
    digitalWrite(_pino2, HIGH);
    digitalWrite(_pino3, HIGH);
    digitalWrite(_pino4, HIGH);
    digitalWrite(_pino5, HIGH);
    digitalWrite(_pino6, HIGH);
    digitalWrite(_pino7, HIGH);
    digitalWrite(_pino8, HIGH);
}

String HTTP_req; 
String URLValue;

void loop()
{
    delay(80); 
    WiFiClient  client = server.available();

    if (client) {
 
  boolean continua = true;
  String linha = "";        

  while (client.connected()) {
    if (client.available()) { 
        char c = client.read(); 
        linha.concat(c); 
    if (c == '\n' && continua )
    { 
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/javascript");
      client.println("Access-Control-Allow-Origin: *");
      client.println();          
     
      int iniciofrente = linha.indexOf("?");
            
      if(iniciofrente>-1){     //verifica se o comando veio
        iniciofrente     = iniciofrente+6; //pega o caractere seguinte
        int fimfrente    = iniciofrente+4; //esse comando espero 3 caracteres
        String acao    = linha.substring(iniciofrente,fimfrente);//recupero o valor do comando
        
        if      ( acao == "00ON"){ digitalWrite(_pino0, LOW); } 
        else if ( acao == "00OF"){ digitalWrite(_pino0, HIGH);}
        
        else if ( acao == "01ON"){ digitalWrite(_pino1, LOW); } 
        else if ( acao == "01OF"){ digitalWrite(_pino1, HIGH);} 
       
        else if ( acao == "02ON"){ digitalWrite(_pino2, LOW); }
        else if ( acao == "02OF"){ digitalWrite(_pino2, HIGH);}
      
        else if ( acao == "03ON"){ digitalWrite(_pino3, LOW); }
        else if ( acao == "03OF"){ digitalWrite(_pino3, HIGH);}
      
        else if ( acao == "04ON"){ digitalWrite(_pino4, LOW); }
        else if ( acao == "04OF"){ digitalWrite(_pino4, HIGH);}
      
        else if ( acao == "05ON"){ digitalWrite(_pino5, LOW); }
        else if ( acao == "05OF"){ digitalWrite(_pino5, HIGH);}
      
        else if ( acao == "06ON"){ digitalWrite(_pino6, LOW); }
        else if ( acao == "06OF"){ digitalWrite(_pino6, HIGH);}
      
        else if ( acao == "07ON"){ digitalWrite(_pino7, LOW); }
        else if ( acao == "07OF"){ digitalWrite(_pino7, HIGH);}
      
        else if ( acao == "08ON"){ digitalWrite(_pino8, LOW); }
        else if ( acao == "08OF"){ digitalWrite(_pino8, HIGH);}

        
        client.print("dados({ ");
        client.print(" _pino0 : ");
        client.print(digitalRead(_pino0));
        client.print(", _pino1 : ");
        client.print(digitalRead(_pino1));
        client.print(", _pino2 : ");
        client.print(digitalRead(_pino2));
        client.print(", _pino3 : ");
        client.print(digitalRead(_pino3));
        client.print(", _pino4 : ");
        client.print(digitalRead(_pino4));
        client.print(", _pino5 : ");
        client.print(digitalRead(_pino5));
        client.print(", _pino6 : ");
        client.print(digitalRead(_pino6));
        client.print(", _pino7 : ");
        client.print(digitalRead(_pino7));
        client.print(", _pino8 : ");
        client.print(digitalRead(_pino8));
        client.print("})");
     }          
      break;
    }
                if (c == '\n') { continua = true; } 
                else if (c != '\r') { continua = false; }
            }
        } 
        delay(50);     
        client.stop(); 
        delay(50);
    } 
}


int verifica_temperatura(byte pinLeituraDoSensor) {
  float voltage = pinLeituraDoSensor * (3.0/1023);
  int temperatura = voltage * 100;
  return temperatura;
}
