/*
  Demonstrates how to do something with the ESP8266Kinto library
*/

// Kinto library
#include <ESP8266Kinto.h>

// We need a WiFi connection
#include <ESP8266WiFi.h>

const char* ssid     = "your-ssid";
const char* password = "your-password";

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
  "CF:8A:24:95:49:F0:5A:1F:3B:EB:15:C0:72:F4:C9:D6:19:3F:EC:FB"
);

void setup()
{
  // initialize serial communication
  Serial.begin(115200);

  // we start by connecting to a WiFi network

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // then we send a message on start
  String json = "{\"data\": {\"board\": \"on\"}}";
  kinto.post(json);
}

void loop()
{
  delay(1);
}
