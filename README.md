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

### Pinagem mcu8266 ###
![esp826612_pinout](https://user-images.githubusercontent.com/37155369/42519887-5e232fbe-843b-11e8-8310-e9d6e01bebc3.jpg)

Configurando Conversor FTDI no ESP8266
==============

1 Passo : Identifique os pinos do seu ESP01  e monte conforme as imagens abaixo (Detalhe: Conectar o pino GPIO0 no terra, antes de ligar o FTDI na entrada USB)
