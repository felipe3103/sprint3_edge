#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "felipefernandes";  // Seu SSID de WiFi
const char* password = "Fetica310306"; // Sua senha de WiFi
const String fiware_url = "http://20.201.119.198:1026/v2/entities/ESP32Device/attrs";

void setup() {
  Serial.begin(115200);
  
  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Iniciar o sensor DHT
  dht.begin();
}

void loop() {
  // Leitura de temperatura e umidade do DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Leitura do sensor LDR (luminosidade)
  int luminosity = analogRead(34);  // Assumindo que o LDR está conectado no pino 34

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Se estiver conectado ao Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(fiware_url);  // Conectar ao Orion Context Broker
    http.addHeader("Content-Type", "application/json");

    // Montando o JSON para envio
    String postData = "{\"temperature\": {\"value\": " + String(temperature) + ", \"type\": \"Float\"}, \"humidity\": {\"value\": " + String(humidity) + ", \"type\": \"Float\"}, \"luminosity\": {\"value\": " + String(luminosity) + ", \"type\": \"Integer\"}}";

    // Enviando dados com requisição PUT
    int httpResponseCode = http.PUT(postData);

    // Verificar a resposta do servidor
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on sending PUT request");
    }

    http.end();  // Finalizar conexão HTTP
  } else {
    Serial.println("WiFi not connected");
  }

  delay(10000);  // Aguarda 10 segundos antes de enviar novamente
}