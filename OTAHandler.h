#pragma once

class AsyncWebServer;

class OTAHandler {
public:
  OTAHandler(const char* ssid, const char* password);

  void init(const String& html);

  static String getCurrentURL();
private:
  const char* wlStatusToString(uint8_t status);

  AsyncWebServer* mServer;

  const char* mSsid;
  const char* mPassword;
};
