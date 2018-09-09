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

### Pinagem módulo Relé 8 ###
![circuito-rele-8-pinos](https://user-images.githubusercontent.com/37155369/44754262-816f5000-aaf7-11e8-812c-e4798ae9841a.jpg)

Configurando Conversor FTDI no ESP8266
==============

1 Passo: Identifique os pinos do seu ESP01  e monte conforme as imagens abaixo (Detalhe: Conectar o pino GPIO0 no terra, antes de ligar o FTDI na entrada USB)

![esp8266pinout1](https://user-images.githubusercontent.com/37155369/42705696-8a58958a-86aa-11e8-923a-75a48937cab4.png)
![sem-titulo-1](https://user-images.githubusercontent.com/37155369/42705701-9138715e-86aa-11e8-95d7-f6673e78fdc5.png)

2 Passo: Conecte o FTDI na porta USB.

_OBS: Em alguns casos, por motivos desconhecidos não é possível subir o código com o GPIO0 conectado ao GND, quando isso acontecer, faça o 1º passo, mas aguarde alguns segundos após conectar o FTDI no USB e retire o GPIO0 do GND._

3 Passo: Instalar a extensão do ESP8266 na IDE do Arduino – de acordo com um dos nossos posts anteriores;

4 Passo: Agora é só fazer upload do código normalmente;

5 Passo: Após ter feito upload, desligue o USB, desconecte o GPIO0 do terra, e conecte o GPIO2( o que está abaixo do GPIO0) no pino de dados do seu sensor;

6 Passo: Conecte o FTDI à entrada USB;

7 Passo: Acompanhe a resposta via serialmonitor.

### Configurando o raspberry como servidor ###
https://www.dobitaobyte.com.br/configurar-um-servidor-ntp-no-raspberry-pi/

#### Instalando o servidor NTP ####
É fácil demais. Simplesmente abra um terminal e digite:

```
sudo apt-get install ntp ntpdate
```

Após isso, edite o arquivo /etc/ntp.conf. Adicione essa linha ao final do arquivo:

```
server 192.168.1.10 prefer
```

Esse IP deve ser o mesmo do seu Raspberry Pi. Seu Raspberry Pi deve ter IP fixo. Para isso, a maneira mais simples é configurar seu servidor DHCP para atribuir sempre o mesmo IP ao Raspberry. Basta configurá-lo em seu roteador, pegando o endereço MAC através do comando ifconfig.

Enfim, após salvar o arquivo você deverá reiniciar o serviço:

```
sudo service ntp restart
```

Apenas ajustar a hora do Raspberry
A primeira coisa que você precisa fazer é garantir que seu timezone está configurado corretamente.

#### Configurar timezone ####
Para configurar seu timezone, execute o comando:

```
sudo dpkg-reconfigure tzdata
```

Selecione America no menu que se abre e procure o timezone da sua região. Quando terminar essa configuração, podemos ir para o próximo passo.


#### Ajustar a data/hora ####
Se você instalar apenas o ntpdate, já pode fazer consultas e ajustes externamente à sua rede. Basta executar o comando:

```
/usr/sbin/ntpdate -q ntp.ubuntu.com
```

Mas com seu servidor devidamente configurado, você pode consultar o próprio Raspberry. Tendo já configurado seu servidor NTP e feito o primeiro ajuste de hora conforme a linha de comando anterior, seu DNS já pode ser iniciado:

```
sudo service bind9 start
```
```
sudo ntpdate -q ns1
```

Lembrando que ns1 é o nome que eu dei para o meu servidor DNS, que não precisa ser o hostname (e talvez nem deva).
