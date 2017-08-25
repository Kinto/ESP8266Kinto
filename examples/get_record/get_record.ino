/*
  Demonstrates how to do something with the ESP8266Kinto library
*/

// Kinto library
#include <ESP8266Kinto.h>

// We need a WiFi connection
#include <ESP8266WiFi.h>
#include <WiFiManager.h>             //https://github.com/tzapu/WiFiManager

// Kinto object creation
Kinto kinto(
  "https://kinto.dev.mozaws.net/v1", // server url
  "login",                           // login
  "password",                        // password
  "default",                         // bucket
  "sensors",                         // collection
  // the server ssl fingerprint is needed for a HTTPS connection
  // get it using the following command in a terminal:
  // echo | openssl s_client -connect kinto.dev.mozaws.net:443 |& openssl x509 -fingerprint -noout
  "14:06:27:FC:60:1E:23:45:36:CF:DB:ED:A5:F1:62:43:C0:2E:BC:28"
);

void setup()
{
  // initialize serial communication
  Serial.begin(115200);

  // we start by connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");

  // we create a buffer
  String json;

  // then we get a record
  json = kinto.getRecord("96992675-24d5-4e87-b009-9c75f5f9e2d3");

  Serial.println(json);
}

void loop()
{
  delay(1);
}
