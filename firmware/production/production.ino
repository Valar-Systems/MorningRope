#include <Arduino.h>
#include "memory.h"
#include "motor_control.h"
#include "api_settings.h"
#include "espui_settings.h"
#include <ArduinoOTA.h>  // For enabling over-the-air updates

void setup() {

  Serial.begin(115200);
  Serial.println("BEGIN SETUP");

  Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);  // ESP32 can use any pins to Serial

  delay(100);

  preferences.begin("local", false);
  load_preferences();
  setup_motors();
  setup_wifi();
  ESPUIsetup();

  ArduinoOTA.begin();

  Serial.println("COMPLETE SETUP");
}

// Variables will change:
int lastStateBtn1 = LOW;  // the previous state from the input pin
int currentStateBtn1;     // the current reading from the input pin
int lastStateBtn2 = LOW;  // the previous state from the input pin
int currentStateBtn2;     // the current reading from the input pin


void loop() {
  dnsServer.processNextRequest();  // Process request for ESPUI
  ArduinoOTA.handle();             // Handles a code update request
  wifiResetButton();

  // read the state of the switch/button:
  currentStateBtn1 = digitalRead(BUTTON_1_PIN);
  currentStateBtn2 = digitalRead(BUTTON_2_PIN);

  if (lastStateBtn1 == HIGH && currentStateBtn1 == LOW) {
    Serial.println("Btn1 is pressed");
    if (is_moving) {
      stop_flag = true;
    } else {
      move_to_percent100ths(0);
    }
  }

  if (lastStateBtn2 == HIGH && currentStateBtn2 == LOW) {
    Serial.println("Btn2 is pressed");
    if (is_moving) {
      stop_flag = true;
    } else {
      move_to_percent100ths(100);
    }
  }

  // save the the last state
  lastStateBtn1 = currentStateBtn1;
  lastStateBtn2 = currentStateBtn2;

}