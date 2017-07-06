# BeerThermometer WebMonitor
These instructions are in portuguese, if you need them in English contact me on guilhermeherzog at gmail.

Este é um projeto que utiliza o módulo wifi NodeMCU com a IDE do Arduino e um Sensor de Temperatura implementado via OneWire.

### Instruções para configurar o projeto:

 1. Baixar o código-fonte neste link: 	Link Código-Fonte:
    https://github.com/guiherzog/BeerThemo	 
    
 2. Adicionar a pasta "OneWire" em /Documentos/Arduino/Libraries.
 3. Seguir o tutorial deste link para configurar o NodeMCU com a IDE do Arduino.
    	http://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/
    	
 4. Abrir o Arduino IDE (Se já nao tiver). 
 5. Alterar o SSID e Password do WIFI de acordo com os seu. 
 6. Compilar o Código.
	    6.1 Caso aconteça algum problema verifique os passos 2 e/ou 3. 
 7. Se compilar corretamente, conecte o NodeMCU ao computador. (Se nao
    tiver já conectado). 
 8. Verifique se a porta serial está selecionada em Tools/Port. 
 9. Faça o Upload (Leva uns 20min) para o NodeMCU. 
 10. Se o NodeMCU estiver conectado ao computador, abra o Serial Monitor
    em Tools/Serial Monitor (`CTRL+SHIFT+M`); 
 11. Caso o upload seja feito corretamente, aperte o RST do NodeMCU. 
 12. Caso a conexão seja bem-sucedida, você verá as informações de Wifi e do IP recebido no Serial Monitor. 	
	 12a. Caso nao consiga ver as informações no Serial Monitor, você pode ver na lista de DHCP do seu roteador o IP atribuido ao sensor. 
 13. Se você chegou até aqui com sucesso, acesse a página do ip do seu sensor. (A minha era 192.168.1.13); 
 14. Caso você queira acessá-lo fora da sua rede Local, você precisa configurar uma entrada na sua tabela NAT do roteador para direcioner o tráfego do seu IP público para o IP do sensor. Se nao souber como fazer, me mande uma mensagem. 
 15. Espero que sua jornada tenha prazerosa e desafiadora :)

> **Recomendações:** o sensor responde as requisições via HTTP, o ideal seria responder via WS (WebSocket).
