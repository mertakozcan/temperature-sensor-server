#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"

#define USE_SERIAL Serial
#define DHTPIN 12 // D6
#define DHTTYPE DHT22

char ssid[] = "SSID";
char password[] = "PASSWORD";

ESP8266WiFiMulti WiFiMulti;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  USE_SERIAL.begin(115200);
  USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for(uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
}

void loop() {
  // wait for WiFi connection
  if((WiFiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("\n");

    USE_SERIAL.print("[HTTP] begin...\n");
    String requestUri = String("/api/v1/sensor_data?temperature=") + String(temperature) + String("&humidity=") + String(humidity);
    http.begin("temperature-sensor-app.herokuapp.com", 80, requestUri);

    USE_SERIAL.print("[HTTP] POST...\n");
    int httpCode = http.POST("");
    USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

    // httpCode will be negative on error
    if(httpCode > 0) {
      if(httpCode == 200 || httpCode == 201) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
      }
    } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  delay(10000);
}

