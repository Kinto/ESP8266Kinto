/*
  ESP8266Kinto.h - Kinto library for ESP8266 Arduino
*/

// ensure this library description is only included once
#ifndef ESP8266Kinto_h
#define ESP8266Kinto_h

// uncomment to activate debugging mode
//#define DEBUG 1

// include description files for other libraries used

// library interface description
class Kinto
{
  // user-accessible "public" interface
  public:
    Kinto(char* server, char* token, char* secret, char* bucket, char* collection, char* fingerprint);
    void post(String json);
    void patch(String id, String json);
    String getRecord(String id);
    String getRecords();
    String getRecords(String filter);

  // library-accessible "private" interface
  private:
    char server[100];
    char fingerprint[100];
    char token[100];
    char secret[100];
    char bucket[100];
    char collection[100];
    String url;
};

#endif
