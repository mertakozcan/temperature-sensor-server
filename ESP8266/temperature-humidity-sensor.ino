#include <DNSServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h> // WiFi Setup
#include "DHT.h"

// Define DHT pin
#define DHTPIN 14 // D5 on board
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Define LED pin
#define REDPIN 13 // D7 on board

// Define HTTP Client
HTTPClient http;

void setup() {
  Serial.begin(115200);

  pinMode(REDPIN, OUTPUT);

  digitalWrite(REDPIN, HIGH); // turn on LED

  // Put ESP8266 in server mode and allow user to communicate with board
  // over WiFi and select the network of his/her choice to connect
  WiFiManager wifiManager;
  // wifiManager.resetSettings(); // For testing only
  wifiManager.autoConnect("KURULUM");

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(REDPIN, LOW); // turn off LED

  // Start DHT sensor
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.printf("Temperature: %f Humidity: %f\n", temperature, humidity);

  if (!isnan(temperature) && !isnan(humidity)) {
    digitalWrite(REDPIN, LOW); // reset LED

    // Make HTTP request
    Serial.println("[HTTP] Begin...");
    String requestUri = String("/api/v1/sensor_data?temperature=") + String(temperature) + String("&humidity=") + String(humidity);
    http.begin("akozcan.herokuapp.com", 80, requestUri);
    int http_code = http.POST("");
    Serial.printf("[HTTP] POST... code: %d\n", http_code);
    http.end();

    // Evaluate HTTP response
    if(http_code == 200 || http_code == 201) {
      delay(300000); // 5 minutes
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(http_code).c_str());
    }
  } else {
    digitalWrite(REDPIN, HIGH); // turn on LED to indicate the problem
  }

}