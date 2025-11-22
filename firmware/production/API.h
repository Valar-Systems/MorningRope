#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"


String ip_address;
String hostname = "VAL3000";

AsyncWebServer serverAPI(8080);

void connectWifi() {
  WiFi.softAPdisconnect(true);
  Serial.println(ssid);
  Serial.println(pass);
  WiFi.mode(WIFI_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid.c_str(), pass.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(1000);
    Serial.print(".");

    if (wifi_button == true)
    {
      Serial.println("Wifi Pressed");
      button_change();
      wifi_button = false;
    }
  }

  Serial.println(WiFi.localIP());
  ip_address = WiFi.localIP().toString();
}

void API()
{

  Serial.print("wifi_set: ");
  Serial.println(wifi_set);

  uint32_t chipid = 0;
  for (int i = 0; i < 17; i = i + 8)
  {
    chipid |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  char ap_ssid[25];
  snprintf(ap_ssid, 26, "VALAR-AP-%08X", chipid);


  if (wifi_set == 0)
  {
    WiFi.softAP(ap_ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
    ip_address = WiFi.softAPIP().toString();
  }
  else if (wifi_set == 1)
  {
    connectWifi();
  }


  serverAPI.on("/position", HTTP_GET, [](AsyncWebServerRequest * request) {

    int paramsNr = request->params();

    for (int i = 0; i < paramsNr; i++) {
      AsyncWebParameter* p = request->getParam(i);
    }

    if (request->hasParam("move_to_percent"))
    {
      move_to_percent = request->getParam("move_to_percent")->value().toInt();
      move_to_step = (max_steps / 100) * move_to_percent;
      Serial.print("move_to_percent: ");
      Serial.println(move_to_percent);
      Serial.print("move_to_step: ");
      Serial.println(move_to_step);
      run_motor = true;
    }
    request->send(200, "text/html", "Great Success");
  });


  serverAPI.on("/settings", HTTP_GET, [](AsyncWebServerRequest * request) {

    DynamicJsonDocument doc(2048);
    doc["position"] = getCurrentPosition();

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
  });


  serverAPI.begin();
}
