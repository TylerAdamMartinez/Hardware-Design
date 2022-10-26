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

#include <WiFi.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <HttpClient.h>

const int LED = 13; // LED pin for debugging
const int RED_PIN = 33;
const int BLUE_PIN = 25;
const int GREEN_PIN = 26;

const int INPUT_BTN = 32; // Input from from button push

// Set WiFi details
const char *ssid = "SSID"; // Put your SSID here
const char *password = "PASSWORD"; // Put your PASSWORD here

// Name of the server we want to connect to
const char kHostname[] = "arduino.cc";
const char kPath[] = "/";

void enableDebugLED() {
    digitalWrite(LED, HIGH);
    Serial.println(F("Turning debug LED to ON"));
}

void disableDebugLED() {
    digitalWrite(LED, LOW);
    Serial.println(F("Turning debug LED to OFF"));
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
  // SEND HTTP REQUEST

  delay(1000);
}