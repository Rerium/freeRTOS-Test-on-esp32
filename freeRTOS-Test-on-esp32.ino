#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FastLED.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include "ds18b20.h"
#include "led.h"
#include "utils.h"



const char* ssid = "SEBIK-NET";
const char* password = "16416919012001";
#define GLED 18

void setup() {
  pinMode(OUTPUT,DATA_PIN);
  pinMode(OUTPUT, GLED);
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  uint8_t conCount = 0;
  while (WiFi.status() != WL_CONNECTED) {

    leds[0] = CRGB::Purple;
    FastLED.show();
    delay(1000);
    leds[0] = CRGB::Black;
    FastLED.show();
    conCount++;
    if (conCount == 10) {
      leds[0] = CRGB::FloralWhite;
      FastLED.show();
      locadataortal();
      break;
    }
    if (WiFi.status() == WL_CONNECTED) {leds[0] = CRGB::Magenta;digitalWrite(GLED, 1);}
  }
  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
    leds[0] = CRGB::Red;
    FastLED.show();
  });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  xTaskCreateUniversal(dsSerial, "read DS to serial ", 8192, NULL, 5, NULL,1);
}

void loop() {
  ArduinoOTA.handle();
 
}
