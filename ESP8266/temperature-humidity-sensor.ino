#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <time.h>

#define DHT_PIN 12 // D6 pin on ESP8266 NodeMCU
#define DHT_TYPE DHT22

ESP8266WiFiMulti WiFiMulti;

// Create a sensor instance
DHT dht(DHT_PIN, DHT_TYPE);

// WiFi login information
char ssid[] = "mert";
char password[] = "24681012";

bool read_data = true;

void setup() {
  //Serial.begin(115200);
  //Serial.setDebugOutput(true);
  //Serial.println();
  //Serial.println();
  //Serial.println();
  for(uint8_t t = 4; t > 0; t--) {
    //Serial.printf("[SETUP] WAIT %d...\n", t);
    //Serial.flush();
    delay(1000);
  }

  // Configure WiFi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  // Configure time server
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
}

void loop() {
  // Wait for WiFi connection
  if((WiFiMulti.run() == WL_CONNECTED)) {
    // Get current time
    time_t now;
    struct tm *timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    int current_hour = timeinfo->tm_hour;
    int current_minute = timeinfo->tm_min;
    //Serial.printf("Current time: %d:%d\n", current_hour, current_minute);

    if (current_hour == 4 && current_minute < 5) {
      read_data = true;
    } else if (current_hour == 9 && current_minute < 5) {
      read_data = true;
    } else if (current_hour == 13 && current_minute < 5) {
      read_data = true;
    } else if (current_hour == 16 && current_minute < 5) {
      read_data = true;
    } else if (current_hour == 20 && current_minute < 5) {
      read_data = true;
    } else if (current_hour == 23 && current_minute < 5) {
      read_data = true;
    }

    if (read_data) {
      HTTPClient http;

      float temperature = dht.readTemperature();
      float humidity = dht.readHumidity();
      //Serial.printf("Temperature: %f Humidity: %f\n", temperature, humidity);

      //Serial.println("[HTTP] Begin...");
      String requestUri = String("/api/v1/sensor_data?temperature=") + String(temperature) + String("&humidity=") + String(humidity);
      http.begin("temperature-sensor-app.herokuapp.com", 80, requestUri);
      
      //Serial.println("[HTTP] POST...");
      int http_code = http.POST("");
      //Serial.printf("[HTTP] POST... code: %d\n", http_code);
      if(http_code == 200 || http_code == 201) {
        String payload = http.getString();
        //Serial.println(payload);
        read_data = false;
      } else {
        //Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(http_code).c_str());
        read_data = true;
      }
      http.end();
    }
  }
  // 5 minutes
  delay(300000);
}

