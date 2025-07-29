/*
 * Simple example for how to use multiple SinricPro Switch device:
 * - setup 4 switch devices
 * - handle request using multiple callbacks
 * 
 * If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 */


#ifdef ENABLE_DEBUG
   #define DEBUG_ESP_PORT Serial
   #define NODEBUG_WEBSOCKETS
   #define NDEBUG
#endif 

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
  #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "WIFI SSID"
#define WIFI_PASS         "PASSWORD"
#define APP_KEY           "APP KEY FROM SINIRIC PRO"
#define APP_SECRET        "APP_SECRET KEY FROM SINIRIC PRO"

#define SWITCH_ID_1       "DEVICE ID"
#define RELAYPIN_1        13

#define SWITCH_ID_2       "DEVICE ID"
#define RELAYPIN_2        12

#define SWITCH_ID_3       "DEVICE ID"
#define RELAYPIN_3        14

#define BAUD_RATE         115200                // Change baudrate to your need

bool onPowerState1(const String &deviceId, bool &state) {
 Serial.printf("Device 1 turned %s", !state?"on":"off");
 digitalWrite(RELAYPIN_1, !state ? HIGH:LOW);
 return true; // request handled properly
}

bool onPowerState2(const String &deviceId, bool &state) {
 Serial.printf("Device 2 turned %s", !state?"on":"off");
 digitalWrite(RELAYPIN_2, !state ? HIGH:LOW);
 return true; // request handled properly
}

bool onPowerState3(const String &deviceId, bool &state) {
 Serial.printf("Device 3 turned %s", !state?"on":"off");
 digitalWrite(RELAYPIN_3, !state ? HIGH:LOW);
 return true; // request handled properly
}

// setup function for WiFi connection
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");

  #if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP); 
    WiFi.setAutoReconnect(true);
  #elif defined(ESP32)