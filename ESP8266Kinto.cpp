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
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
};

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in ESP8266Kinto sketches, this library, and other libraries

void Kinto::post(String json) {
  digitalWrite(LED_BUILTIN, LOW);

  #ifdef DEBUG
  Serial.println(url);
  Serial.println(json);
  #endif

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

void Kinto::patch(String id, String json) {
  digitalWrite(LED_BUILTIN, LOW);

  String recordUrl = url +  + "/" + id;

  #ifdef DEBUG
  Serial.println(recordUrl);
  Serial.println(json);
  #endif

  HTTPClient http;
  if (server[4] == 's') {
    http.begin(recordUrl, fingerprint);
  }
  else {
    http.begin(recordUrl);
  }
  http.addHeader("Content-Type", "application/json");
  http.setAuthorization(token, secret);
  http.sendRequest("PATCH", (uint8_t *) json.c_str(), json.length());
  http.end();

  digitalWrite(LED_BUILTIN, HIGH);
};

String Kinto::getRecord(String id) {
  String json; // buffer
  String url1 = url + "/" + id;

  digitalWrite(LED_BUILTIN, LOW);

  #ifdef DEBUG
  Serial.println(url1);
  Serial.println(json);
  #endif

  HTTPClient http;
  if (server[4] == 's') {
    http.begin(url1, fingerprint);
  }
  else {
    http.begin(url1);
  }
  http.addHeader("Accept", "application/json");
  http.setAuthorization(token, secret);
  int httpCode = http.GET();
  if (httpCode > 0 ){
    // HTTP header has been send and Server response header has been handled

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      json = http.getString();
    }
  }
  http.end();

  digitalWrite(LED_BUILTIN, HIGH);

  return json;
};

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
