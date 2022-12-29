#include "OTAHandler.h"

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

OTAHandler::OTAHandler(const char* ssid, const char* password) : mServer(new AsyncWebServer(80)), mSsid(ssid), mPassword(password) {
  
}

void OTAHandler::init(const String& html) {
  Serial.println("Initialising OTA.");
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect(true);
    Serial.println("Previous connection disconnected.");
  }

  WiFi.mode(WIFI_STA);
  WiFi.persistent(false);
  WiFi.setAutoReconnect(true);
  WiFi.setSleep(false);

  if (WiFi.begin(mSsid, mPassword)) {
    Serial.println("WiFi begin success");
  }
  
  delay(2000);

  uint8_t wifiStatus = WiFi.waitForConnectResult();

  if ((wl_status_t)wifiStatus != WL_CONNECTED) {
    Serial.println(String("WiFi Status: ") + wlStatusToString(wifiStatus) + ", exiting...");
    while (true);
  }

  Serial.println(String("SSID - ") + WiFi.SSID().c_str());
  Serial.println(String("IP   - ") + WiFi.localIP().toString().c_str());
  Serial.println(String("MAC  - ") + WiFi.macAddress().c_str());

  mServer->on("/whoami", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Sending whoami response.");
    request->send(200, "text/plain", "Description goes here");
    Serial.println("Sent whoami response.");
  });

  mServer->on("/", HTTP_GET, [html](AsyncWebServerRequest* request) {
    Serial.println("Sending main response.");
    request->send(200, "text/html", html);
    Serial.println("Sent main response.");
  });

  mServer->on("/print_debug", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", "Yo");
  });

  AsyncElegantOTA.begin(mServer);
  mServer->begin();

  Serial.println("OTA init complete...");
}

String OTAHandler::getCurrentURL() {
  return String((char*)(WiFi.localIP()).toString().c_str());
}

const char* OTAHandler::wlStatusToString(uint8_t status) {
  switch ((wl_status_t) status) {
    case WL_NO_SHIELD:       return "WL_NO_SHIELD";
    case WL_IDLE_STATUS:     return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL:   return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED:  return "WL_SCAN_COMPLETED";
    case WL_CONNECTED:       return "WL_CONNECTED";
    case WL_CONNECT_FAILED:  return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED:    return "WL_DISCONNECTED";
    default:                 return "UNKNOWN";
  }
}
