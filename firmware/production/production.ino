#include <Arduino.h>
#include <ESPUI.h>

#include <TMCStepper.h>
#include <Preferences.h>
#include "Memory.h"
#include "ResetButton.h"
#include "MotorControl.h"
#include "API.h"
#include <EEPROM.h>
#include <ArduinoOTA.h>  // For enabling over-the-air updates

void setup() {

  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);  // ESP32 can use any pins to Serial

  delay(100);
  preferences.begin("local", false);
  load_preferences();
  setup_motors();
  API();
  ESPUIsetup();
}

void loop() {

  dnsServer.processNextRequest();  // Process request for ESPUI
  ArduinoOTA.handle();  // Handles a code update request

  if (btn1Press == 1 & btn2Press == 1) {

    Serial.println("change direction of motor");

  }

  else if (btn1Press == 1) {
    button1Timer = millis();
    waitButton2Timer = millis() + 1000;

    if (motorRunning) {
      Serial.println("STOP MOTOR");
      stop();
    } else if (millis() < waitButton2Timer && btn2Press == 1) {
      Serial.println("START MOTOR CLOSE");
      motorRunning = true;
      is_closing = true;
      move_to_percent100ths(0);
    }
  } else if (btn2Press == 1) {
    button1Timer = millis();
    waitButton2Timer = millis() + 1000;

    if (motorRunning) {
      Serial.println("STOP MOTOR");
      stop();
    } else if (millis() < waitButton2Timer && btn2Press == 1) {
      Serial.println("START MOTOR CLOSE");
      motorRunning = true;
      is_closing = false;
      move_to_percent100ths(100);
    }
  } else {
    vTaskDelay(1);
  }
}



// if (run_motor == true) {
//   Serial.println("Run Motor Function");
//   move_motor();
//   run_motor = false;
//   ESPUI.updateLabel(positionLabel, String(int(((float)current_position / (float)max_steps) * 100)));
//   Serial.println("Motor Complete");
// } else if (set_zero == 1) {
//   setZero();
//   set_zero = 0;
// } else if (wifi_button == true) {
//   button_change();
//   wifi_button = false;
// } else {
//   vTaskDelay(1);
// }
// }
// }
