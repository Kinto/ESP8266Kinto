/*
  ESP8266Kinto.h - Kinto library for ESP8266 Arduino
*/

// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "ESP8266Kinto.h"

// include description files for other libraries used
#include "ESP8266HTTPClient.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Kinto::Kinto(char* server, char* token, char* secret, char* bucket, char* collection, char* fingerprint = "")
{
  // initialize this instance's variables
  strcpy(this->server, server);
  strcpy(this->fingerprint, fingerprint);
  strcpy(this->token, token);
  strcpy(this->secret, secret);
  strcpy(this->bucket, bucket);
  strcpy(this->collection, collection);
  this->url = String(server) + "/buckets/" + String(bucket) + "/collections/" + String(collection) + "/records";

  // do whatever is required to initialize the library
  //Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
};

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in ESP8266Kinto sketches, this library, and other libraries

void Kinto::post(String json) {
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println(url);
  Serial.println(json);
  HTTPClient http;
  if (server[4] == 's') {
    http.begin(url, fingerprint);
  }
  else {
    http.begin(url);
  }
  http.addHeader("Content-Type", "application/json");
  http.setAuthorization(token, secret);
  http.POST(json);
  http.end();

  digitalWrite(LED_BUILTIN, HIGH);
};

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library