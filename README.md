Arduino Ethernet com Ajax
==============

Arduino recebendo uma requisição AJAX e retornando um json.


Download de todos os arquivos: https://github.com/rogerin/ArduinoComAjax/archive/master.zip



Arduino Wifi ESP8266 com Ajax
==============

### Configurar preferencias para instalar ESP8266 ###

```
http://arduino.esp8266.com/versions/2.4.1/package_esp8266com_index.json
```
### Esquema de ligação ###
![conexao simples_bb](https://user-images.githubusercontent.com/37155369/42415746-d0c78c9e-822f-11e8-977b-344eb1a1c65b.png)
![conexao simples_esquematico](https://user-images.githubusercontent.com/37155369/42415770-3205cd3a-8231-11e8-917e-0407ebcff26b.png)
#### Configuração Básica:

| Comando                      | Ação | Observação |
|------------------------------|------|------------|
| AT+RST                       | Reset do Módulo      |            |
| AT                           | Teste de envio de Comandos     |            |
| AT+GMR                       | Versão do Firmware     |            |
| AT+CWLAP                     | Listagem das Redes WiFi Disponíveis     |            |
| AT+CWJAP="rede-wifi","senha" | Conexão a rede WiFi especificada    |            |
| AT+CWMODE=1                  | Modo de Operação     | Servidor            |
| AT+CIFSR                     | Mostrar IP Atual     |            |
| AT+CIPMUX=1                  | Modo de Múltiplas Conexões     | Habilitado           |
| AT+CIPSERVER=1,80            | Modo Servidor TCP     | Servidor Criado na Porta 80           |
| AT+CIPSEND=0,93              | Envio de Informações ao requisitante     | Após requisitar no browser a informação pode ser enviada via Serial Monitor:Enviar no Canal 0(zero) ```<head><meta http-equiv=""refresh"" content=""3""></head><h1><u>ESP8266 - Web Server</u></h1>```            |
| AT+CIPCLOSE=0                | Encerrar o envio     | Ap
