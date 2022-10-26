/*
 HTTP Client

 This program drives a brush and brushless DC motor.
 The motor is attached to digital pins 3 and 9 of the Arduino.

 The motor spins at Full rotation speed for 2 seconds,
 then half the rotation speed for 2 seocnds,
 and then no movement from motor for 2 seconds. 

 Created October 25, 2022
 by Tyler Adam Martinez 

 */



#include "WiFi.h"
#include "ArduinoJson.h"
#include <stdlib.h>

//Http POST
#include "HTTPClient.h"

// Chip select pin for SLI
const int LED = 13; // LED pin for debugging

const int RED_PIN = 33;
const int BLUE_PIN = 25;
const int GREEN_PIN = 26;

const int INPUT_BTN = 32; // Input from from button push

// Set WiFi details
const char *ssid = "SSID"; // Put your SSID here
const char *password = "PASSWORD"; // Put your PASSWORD here

static const size_t spiBufferSize = 1024;
static uint8_t spiBuffer[spiBufferSize] = {0xFF};

void enableDebugLED() {
    digitalWrite(LED, HIGH);
    Serial.println(F("Turning debug LED to ON"));
}

void disableDebugLED() {
    digitalWrite(LED, LOW);
    Serial.println(F("Turning debug LED to OFF"));
}


void sendData(uint8_t * payload, size_t len) {
  Serial.print(F("About to send data to server, len: "));
  Serial.println(len);
  HTTPClient http;

  http.setTimeout(120000);

  http.begin("http://hat-or-not.helpfulseb.com:8080/ingest/outfit"); 
  http.addHeader("Content-Type", "Content-Type: image/jpeg"); 

  int httpResponseCode = http.POST(payload, len);

  if (httpResponseCode >= 0) {
    String response = http.getString();  //Get the response to the request
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
    const size_t capacity = 256; //Based on this website https://arduinojson.org/v6/assistant/
    DynamicJsonDocument doc(capacity);

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, response);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

    printRGB(doc["clothingColour"].as<char*>());

    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
  http.end();
}

void setup() {  
  uint8_t vid, pid;
  uint8_t temp;
  
  // Set the LED pins as an outputs
  pinMode(LED, OUTPUT);

  // Set the RGB LED pins as an outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Wire.begin();

  Serial.begin(115200);
 
  if (!strcmp(ssid, "SSID")) {
    Serial.println(F("Please set your WiFi SSID"));
    while(1);
  }
  if (!strcmp(password, "PASSWORD")) {
    Serial.println(F("Please set your WiFi PASSWORD"));
    while(1);
  }

  // Connect to WiFi network
  Serial.printf("Connecting to %s", ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(750);
    Serial.println(F("."));
  }
  Serial.print(F("WiFi connected: "));
  Serial.println(WiFi.localIP());

}

void loop() {
  // SEND HTTP REQUEST

  delay(1000);
}
