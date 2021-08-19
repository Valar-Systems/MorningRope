#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

const char *ap_ssid = "VALAR-AP";
const char *ap_password = "password";

String ip_address;

AsyncWebServer server(80);

const char WIFI_HTML[] = "Enter your home Wifi Name and Password <br> <br> <form action=\"/set_wifi\">\n    <label class=\"label\">Network Name</label>\n    <input type = \"text\" name = \"ssid\"/>\n    <br/>\n    <label>Network Password</label>\n    <input type = \"text\" name = \"pass\"/>\n    <br/>\n    <input type=\"submit\" value=\"Set Values\">\n</form>";
const char SETTINGS_HTML[] = "<h2>Valar Systems</h2>\n<h3>Motion Control</h3>\n<p>To learn more, please visit <a href=\"https://help.valarsystems.com/docs/VAL-1000/VAL-1000\">https://help.valarsystems.com</a></p>\n<p>To add this device to your network <a href=\"http://192.168.4.1/wifi\">go to http://192.168.4.1/wifi</a></p>\n<p>To remove this device from your network, press and hold the wifi reset button for 3+ seconds.</p>\n<br> \n<h2>Position</h2>\n<form action=\"/position\">\n    <p>Enter a value from 0-100. This is the percent of the max_steps value to move the motor.</p>\n    <label><b>move_to :</b></label>\n    <input value = \"%PLACEHOLDER_PERCENT%\" type = \"text\" name = \"move_percent\"/>\n    <br/>\n    <input type=\"submit\" value=\"Set Position\">\n    <p>You can also send an HTTP request to http://%PLACEHOLDER_IP_ADDRESS%/position?move_percent=%PLACEHOLDER_PERCENT%</p>\n</form>\n<br>\n<h2>Motor Parameters</h2>\n<form action=\"/set_motor\">\n    <p>Enter a value from 400-2000. This is the amount of RMS current the motor will draw.</p>\n    <label><b>current</b></label>\n    <input value = \"%PLACEHOLDER_CURRENT%\" type = \"text\" name = \"current\"/>\n    <p>You can also send an HTTP request to http://%PLACEHOLDER_IP_ADDRESS%/set_motor?current=%PLACEHOLDER_MAX_STEPS%</p>\n    <br/>\n    <p>Enter a stall value from 0-255. The higher the value, the easier it will stall.</p>\n    <label><b>stall</b></label>\n    <input value = \"%PLACEHOLDER_STALL%\" type = \"text\" name = \"stall\"/>\n    <p>You can also send an HTTP request to http://%PLACEHOLDER_IP_ADDRESS%/set_motor?stall=%PLACEHOLDER_STALL%</p>\n    <br/>\n        <input type=\"submit\" value=\"Set Parameters\">\n<p>To set all values at once, send an HTTP request to http://%PLACEHOLDER_IP_ADDRESS%/set_motor?max_steps=%PLACEHOLDER_MAX_STEPS%&amp;current=%PLACEHOLDER_CURRENT%&stall=%PLACEHOLDER_STALL%&accel=%PLACEHOLDER_ACCEL%&max_speed=%PLACEHOLDER_MAX_SPEED%</p>\n</form>\n<br>\n<br>\n<p>Press this button to set the home position of your motor to zero</p>\n<form action=\"/set_zero\">\n<input type=\"hidden\" name=\"set_zero\" value=\"1\" />\n<input type=\"submit\" value=\"set_zero\">\n</form>";
String processor(const String& var)
{
 
  if(var == "PLACEHOLDER_PERCENT"){
    return String(move_percent);
  }
  else if(var == "PLACEHOLDER_MAX_STEPS"){
    return String(max_steps);
  }
  else if(var == "PLACEHOLDER_CURRENT"){
    return String(current);
  }
  else if(var == "PLACEHOLDER_STALL"){
    return String(stall);
  }
  else if(var == "PLACEHOLDER_ACCEL"){
    return String(accel);
  }
  else if(var == "PLACEHOLDER_MAX_SPEED"){
    return String(max_speed);
  }
  else if(var == "PLACEHOLDER_IP_ADDRESS"){
    return String(ip_address);
  }
 
  return String();
}

void API()
{
    //Preferences library create varaiable to save
  Serial.print("wifi_set: ");
  Serial.println(wifi_set);
  
  if (wifi_set == 0) 
  {
  WiFi.softAP(ap_ssid, ap_password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  ip_address = WiFi.softAPIP().toString();
  }
  else if (wifi_set == 1)
  {
  WiFi.softAPdisconnect(true);
  Serial.println(ssid);
  Serial.println(pass);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());

      while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        
  Serial.println(WiFi.localIP());
  ip_address = WiFi.localIP().toString();
  }
  
  server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", WIFI_HTML);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", SETTINGS_HTML, processor);
  });

  server.on("/set_wifi", HTTP_GET, [] (AsyncWebServerRequest *request) {
    
  if (request->hasParam("ssid")) {
      ssid = request->getParam("ssid")->value().c_str();
      preferences.putString ("ssid", ssid);
      Serial.print("ssid: ");
      Serial.println(ssid);
      Serial.print("ssid preferences: ");
      Serial.println(preferences.getString ("ssid", "NO_SSID"));
    }
    
  if (request->hasParam("pass")) {
      pass = request->getParam("pass")->value().c_str();
      preferences.putString ("pass", pass);
      wifi_set = 1;
      preferences.putInt ("wifi_set", 1);
      
      Serial.println(pass);
      Serial.println(preferences.getString ("pass", "NO_PASSWORD"));
      
      request->send(200, "text/html", "WiFi Credentials Set. Connect to your home WiFi network, find the IP address of this device, and go to http://NEW-IP-ADDRESS");
      WiFi.softAPdisconnect(true);
      delay(500);
      WiFi.begin(ssid.c_str(), pass.c_str());  

    }
                                  
  });

  server.on("/set_motor", HTTP_GET, [](AsyncWebServerRequest *request){
    
    int paramsNr = request->params();
    Serial.print("Params: ");
    Serial.println(paramsNr);
 
    for(int i=0;i<paramsNr;i++){
        AsyncWebParameter* p = request->getParam(i);
    }
    
    if(request->hasParam("max_steps"))
        {
          max_steps = request->getParam("max_steps")->value().toInt();
          preferences.putInt ("max_steps", max_steps);
          Serial.print("max_steps: ");
          Serial.println(max_steps);
        }
    if(request->hasParam("current"))
        {
          current = request->getParam("current")->value().toInt();
          driver.rms_current(current); 
          preferences.putInt ("current", current);
          Serial.print("current: ");
          Serial.println(current);
        }
    if(request->hasParam("stall"))
        {
          stall = request->getParam("stall")->value().toInt();
          driver.SGTHRS(stall);
          preferences.putInt ("stall", stall);
          Serial.print("stall: ");
          Serial.println(stall);
        }
    if(request->hasParam("accel"))
        {
          accel = request->getParam("accel")->value().toInt();
          stepper.setAcceleration(accel);
          preferences.putInt ("accel", accel);
          Serial.print("accel: ");
          Serial.println(accel);
        }
    if(request->hasParam("max_speed"))
        {
          max_speed = request->getParam("max_speed")->value().toInt();
          stepper.setMaxSpeed(max_speed);
          preferences.putInt ("max_speed", max_speed);
          Serial.print("max_speed: ");
          Serial.println(max_speed);
        }

    request->redirect("/");
    
  });

server.on("/set_zero", HTTP_GET, [](AsyncWebServerRequest *request){

    int paramsNr = request->params();
 
    for(int i=0;i<paramsNr;i++){
        AsyncWebParameter* p = request->getParam(i);
    }

    set_zero = 1;
    Serial.print("set_zero: ");
    Serial.println(set_zero);   
    request->redirect("/");
  
  });

server.on("/position", HTTP_GET, [](AsyncWebServerRequest *request){
    
    int paramsNr = request->params();
  
    for(int i=0;i<paramsNr;i++){
        AsyncWebParameter* p = request->getParam(i);
    }

    if(request->hasParam("move_percent"))
    {
        move_percent = request->getParam("move_percent")->value().toInt();
        move_to = (max_steps/100)*move_percent;
        stepper.moveTo(move_to);
        Serial.print("max_steps: ");
        Serial.println(max_steps); 
        Serial.print("move_percent: ");
        Serial.println(move_percent); 
        Serial.print("move_to: ");
        Serial.println(move_to); 
        run_motor=true;
    }  

    request->redirect("/");
  
  });

server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request){

DynamicJsonDocument doc(100);
doc["percent_position"] = int(((float)stepper.currentPosition()/(float)max_steps)*100);
doc["steps_position"] = stepper.currentPosition();
doc["max_steps"] = max_steps;
doc["current"] = current;
doc["stall"] = stall;

String json;
serializeJson(doc, json);

request->send(200, "application/json", json);
});

  server.begin();
}
