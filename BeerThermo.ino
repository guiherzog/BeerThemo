// Biblioteca para Leitura do Termometro
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include "FS.h"
 
const char* ssid = "HERZOG LIVETIM";
const char* password = "umbrella";

WiFiServer server(80);

int pinThermometer = 2; // Equivale ao D4 no NodeMCU

// Cria um novo termometro com base no pino declarado.
OneWire ds(pinThermometer);

void setup(void) {
  // Inicia a conexão serial
  Serial.begin(115200);

  // Chama método para iniciar o WiFi.
  setupWifi();
}

void loop(void) {
  // Lê a temperatura
  float temperature = getTemp();
  Serial.println(temperature);

  sendTempToClient(temperature);
  delay(1000); // Espera por 1 segundo.

}

// Função para leitura da temperatura
float getTemp() {
  //returns the temperature from one DS18S20 in DEG

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
    //no more sensors on chain, reset search
    ds.reset_search();
    Serial.println("Reset Search");
    return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  Serial.println(TemperatureSum);
  return TemperatureSum;
}

// Função para iniciar conexão WiFi.
void setupWifi(){
  // Connect to WiFi network
  Serial.println();
  Serial.print("Conectando à ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

// Funçào para enviar temperatura para página:
void sendTempToClient(float temp) {
  // Verifica se o usuário conectou.
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Envia uma página básica HTML com a temperatura.
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // Essa linha é necessária.
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Temperatura: ");
  client.print(temp);
  client.print(" C");
  client.println("<br><br>");
  client.println("</html>");
}
