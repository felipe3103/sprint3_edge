#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4           // Pino ao qual o sensor DHT está conectado
#define DHTTYPE DHT22      // Tipo do sensor DHT (DHT11 ou DHT22)
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Wokwi-GUEST";  // Nome da rede Wi-Fi
const char* password = "";         // Senha da rede (nenhuma para Wokwi-GUEST)
const String fiware_url = "http://4.228.227.116/v2/entities/ESP32Device/attrs";  // Endpoint FIWARE

void setup() {
  Serial.begin(115200);
  
  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP()); // Exibir o IP atribuído

  // Iniciar o sensor DHT
  dht.begin();
}

void loop() {
  // Leitura de temperatura e umidade do DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Leitura do sensor LDR (luminosidade)
  int luminosity = analogRead(34);  // Assumindo que o LDR está conectado no pino 34

  // Verificação de erros na leitura do sensor DHT
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Verifica se está conectado ao Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(fiware_url);  // Conectar ao Orion Context Broker
    http.addHeader("Content-Type", "application/json");

    // Montar o JSON para enviar
    String postData = "{\"temperature\":{\"value\":" + String(temperature, 2) + ",\"type\":\"Float\"},"
                      "\"humidity\":{\"value\":" + String(humidity, 2) + ",\"type\":\"Float\"},"
                      "\"luminosity\":{\"value\":" + String(luminosity) + ",\"type\":\"Integer\"}}";

    // Exibir o JSON no Serial Monitor
    Serial.println("Enviando dados para FIWARE:");
    Serial.println(postData);

    // Enviando dados com requisição PUT
    int httpResponseCode = http.PUT(postData);

    // Verificar a resposta do servidor
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on sending PUT request: " + String(httpResponseCode));
    }

    http.end();  // Finalizar conexão HTTP
  } else {
    Serial.println("WiFi not connected");
  }

  delay(10000);  // Aguardar 10 segundos antes de enviar novamente
}
