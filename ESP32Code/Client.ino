/*
 HTTP Client

 This program gets information from a server.

 It connects to the server using HTTPS GET method.
 The HTTP response's body is a JSON object. The program 
 deserializes the JSON object and uses that data to light an 
 RGB LED to UNT Green.

 Created October 25, 2022
 by Tyler Adam Martinez 

 */

#include <WiFi.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const int LED = 13; // LED pin for debugging
const int RED_PIN = 33;
const int BLUE_PIN = 25;
const int GREEN_PIN = 26;

// Set WiFi details
const char *ssid = "SSID"; // Put your SSID here
const char *password = "PASSWORD"; // Put your PASSWORD here

void enableDebugLED() {
    digitalWrite(LED, HIGH);
    Serial.println(F("Turning debug LED to ON"));
}

void disableDebugLED() {
    digitalWrite(LED, LOW);
    Serial.println(F("Turning debug LED to OFF"));
}

void turnOnRGB(int r, int g, int b) {
    analogWrite(RED_PIN, r);
    analogWrite(GREEN_PIN, g);
    analogWrite(BLUE_PIN, b);
    Serial.println(F("Turning RGB LED to ON"));
    
    // Displaying RBG values to Serial Monitor
    Serial.print(F("Values => R:"));
    Serial.print(F(r));
    Serial.print(F(" G:"));
    Serial.print(F(g));
    Serial.print(F(" B:"));
    Serial.println(F(b));
}

void turnOffRGB() {
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    Serial.println(F("Turning RGB LED to OFF"));
}

void sendRequest() {
    WiFiClientSecure client;
    HTTPClient http;
    
    // Send request
    http.useHTTP10(true);
    http.begin(client, "https://raw.githubusercontent.com/TylerAdamMartinez/Hardware-Design/master/Assets/unt_green.json");
    http.GET();
    
    // Parse response
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getStream());
    
    // Read values
    Serial.println(http.getString());
    int redValue = doc["RGB"][0].as<int>();
    int greenValue = doc["RGB"][2].as<int>();
    int blueValue = doc["RGB"][1].as<int>();
    

    // Disconnect
    http.end();
    
    // Turn RGB LED ON
    turnOnRGB(redValue, greenValue, blueValue);

    // Delay
    delay(1000);
}

void setup() {    
    // Set the LED pins as an outputs
    pinMode(LED, OUTPUT);

    // Set the RGB LED pins as an outputs
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

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
    Serial.print(F("Connecting to "));
    Serial.println(F(ssid));

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(750);
      Serial.println(F("."));
    }
    Serial.print(F("WiFi connected: "));
    Serial.println(WiFi.localIP());

}

void loop() {
    sendRequest();
    turnOffRGB();
    delay(1000);
}