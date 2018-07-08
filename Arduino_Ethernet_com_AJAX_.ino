/*
 * Projeto: Arduino com AJAX
 * Autor: Rogerio Alencar Filho
 * Data: 24/02/2014
 * Versão: v0.1
 * Descrição: O Arduino recebe uma requisição HTTP e retorna um JSON que é tratado no HTML com Javascript para exibir na tela.
 * Github: https://github.com/rogerin/ArduinoComAjax
 * Twitter: https://twitter.com/rogerin
 */


//#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x83, 0xEA};

/*
IPAddress ip(192,168,0,20); // Configure um IP válido 
byte gateway[] = { 192 , 168, 0, 20 }; //Entre com o IP do Computador onde a Câmera esta instalada
byte subnet[] = { 255, 255, 255, 0 }; //Entre com a Máskara de Subrede
EthernetServer server(80); //Inicializa a biblioteca EthernetServer com os valores de IP acima citados e configura a porta de acesso(80)
*/

IPAddress ip(192,168,0,20);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

EthernetServer server(1000);

const int analogPin1 = A1;

int sensor1 = 0;

#define _pino0 0
#define _pino1 1
#define _pino2 2
#define _pino3 3
#define _pino4 4
#define _pino5 5
#define _pino6 6
#define _pino7 7
#define _pino8 8
#define pinSom 9
#define tempoMaximoDeUmaPalma  150 //milisegundos
#define tempoMaximoEntrePalmas 400 //milisegundos

int contaPalmas = 0;
long tempoEspera = 0;
long tempoEsperaEntrePalmas = 0;

void executarAcao();

void setup()
{
  //Serial.begin(9600);
  //Serial.println("Iniciando programa..");
  Ethernet.begin(mac,ip,gateway,subnet);
  //Serial.println("Server ativo no IP: ");
  //Serial.print(Ethernet.localIP());
  server.begin();
  
  pinMode(_pino0, OUTPUT);
  pinMode(_pino1, OUTPUT);
  pinMode(_pino2, OUTPUT);
  pinMode(_pino3, OUTPUT);
  pinMode(_pino4, OUTPUT);
  pinMode(_pino5, OUTPUT);
  pinMode(_pino6, OUTPUT);
  pinMode(_pino7, OUTPUT);
  pinMode(_pino8, OUTPUT);
  pinMode(pinSom, INPUT);

  
  digitalWrite(_pino0, LOW);
  digitalWrite(_pino1, LOW);
  digitalWrite(_pino2, LOW);
  digitalWrite(_pino3, LOW);
  digitalWrite(_pino4, LOW);
  digitalWrite(_pino5, LOW);
  digitalWrite(_pino6, LOW);
  digitalWrite(_pino7, LOW);
  digitalWrite(_pino8, LOW);
  digitalWrite(pinSom, LOW);
}

void loop()
{
  //verifica o estado do sensor de som (ele fica normalmente com a porta ligada. Quando ouver uma palma, ele desliga momentaneamente a porta)
  int sensorSom = digitalRead(pinSom);

  //se o sensor detectou palmas
  if (sensorSom == LOW) {

     //espera um tempo para nao detectar a mesma palma mais de uma vez 
     if (tempoEspera == 0) {
        tempoEspera = tempoEsperaEntrePalmas = millis(); 
        contaPalmas++;
     } else if ((millis() - tempoEspera) >= tempoMaximoDeUmaPalma) {
        tempoEspera = 0;
     }
  }

  //caso exceda o tempo maximo entre palmas, zera o contador de palmas
  if ( (contaPalmas != 0) && ((millis() - tempoEsperaEntrePalmas) > 500) ) {
     executarAcao();
     contaPalmas = 0;
     tempoEsperaEntrePalmas = millis();
  }

  EthernetClient client = server.available();
  if(client)
  {
    boolean continua = true;
    String linha = "";

    while(client.connected())
    {
      if(client.available()){
        char c = client.read();
        linha.concat(c);
  
        if(c == '\n' && continua)
        {
          client.println("HTTP/1.1 200 OK");
          // IMPORTANTE, ISSO FAZ O ARDUINO RECEBER REQUISIÇÃO AJAX DE OUTRO SERVIDOR E NÃO APENAS LOCAL.
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
            else if ( acao == "02OF"){ digitalWrite(_pino2, HIGH); }
          
            else if ( acao == "03ON"){ digitalWrite(_pino3, LOW); }
            else if ( acao == "03OF"){ digitalWrite(_pino3, HIGH); }
          
            else if ( acao == "04ON"){ digitalWrite(_pino4, LOW); }
            else if ( acao == "04OF"){ digitalWrite(_pino4, HIGH); }
          
            else if ( acao == "05ON"){ digitalWrite(_pino5, LOW); }
            else if ( acao == "05OF"){ digitalWrite(_pino5, HIGH); }
          
            else if ( acao == "06ON"){ digitalWrite(_pino6, LOW); }
            else if ( acao == "06OF"){ digitalWrite(_pino6, HIGH); }
          
            else if ( acao == "07ON"){ digitalWrite(_pino7, LOW); }
            else if ( acao == "07OF"){ digitalWrite(_pino7, HIGH); }
          
            else if ( acao == "08ON"){ digitalWrite(_pino8, LOW); }
            else if ( acao == "08OF"){ digitalWrite(_pino8, HIGH); }
          
            //else if ( acao == "09ON"){ digitalWrite(_pino9, LOW); }
            //else if ( acao == "09OF"){ digitalWrite(_pino9, HIGH); }
  
            sensor1 = temperatura(analogRead(analogPin1));
            //Serial.println(temperatura(analogRead(analogPin1)));            
            client.print("dados({ temperatura : ");
            client.print(sensor1);
            client.print(", _pino0 : ");
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
            //client.print(", _pino9 : ");
            //client.print(digitalRead(_pino9));
            client.print("})");
            
         }          
          break;
        }
        if(c == '\n') { continua = true; }
        else if (c != '\r') { continua = false; }
      }
    }
     delay(1);
     client.stop();
  }


}

void executarAcao() 
{
  
  switch (contaPalmas) {
    case 2: 
       digitalWrite(_pino8, !digitalRead(_pino8));
       break;
    case 3:
       digitalWrite(_pino7, !digitalRead(_pino7));
       break;
    case 4:
       digitalWrite(_pino6, !digitalRead(_pino6));
       break;
  }
}

int temperatura(byte pinLeituraDoSensor) {
  float voltage = pinLeituraDoSensor * (5.0/1023);
  int temperatura = voltage * 100;
  return temperatura;
}
          
          /*
          
          #####################
          ## Debug na serial ##
          #####################
          
          sensor1 = analogRead(analogPin1);
          delay(10);
          sensor2 = analogRead(analogPin2);
          
          Serial.println("dados({ \'sensor1\' : ");
          delay(10);
          Serial.println(sensor1);
          delay(10);
          Serial.println(" , \'sensor2\' :  ");
          delay(10);
          Serial.println(sensor2);
          delay(10);
          Serial.println(" }) "); 
          delay(500);
          */

