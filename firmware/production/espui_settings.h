uint16_t openLabel;
uint16_t closeLabel;
uint16_t labelWifi;
uint16_t wifi_ssid_text, wifi_pass_text;
uint16_t speedMax;
uint16_t accelMax;
String display_wifi;

DNSServer dnsServer;

//Function Prototypes
//void textCallback(Control *sender, int type);
//void enterWifiDetailsCallback(Control *sender, int type);

void numberMaxStepsCall(Control* sender, int type) {
  maximum_motor_position = sender->value.toInt();
  preferences.putInt("max_motor_pos", maximum_motor_position);
  Serial.print("maximum_motor_position: ");
  Serial.println(maximum_motor_position);
}

void numberSpeedCall(Control* sender, int type) {
  max_speed = sender->value.toInt();
  preferences.putInt("max_speed", max_speed);
  //setSpeedInHz(max_speed);
  Serial.print("max_speed: ");
  Serial.println(max_speed);
}

void numberAccelCall(Control* sender, int type) {
  accel = sender->value.toInt();
  preferences.putInt("accel", accel);
  //setAcceleration(accel);
  Serial.print("accel: ");
  Serial.println(accel);
}

void numberCurrentCall(Control* sender, int type) {
  current = sender->value.toInt();
  preferences.putInt("current", current);
  Serial.print("current: ");
  Serial.println(current);
}

void numberStallCall(Control* sender, int type) {
  Serial.println(sender->value);
  stall = sender->value.toInt();
  driver.SGTHRS(stall);
  preferences.putInt("stall", stall);
  Serial.print("stall: ");
  Serial.println(stall);
}

void numberTravelCall(Control* sender, int type) {
  Serial.println(sender->value);
  travel_distance = sender->value.toInt();
  preferences.putInt("travel_dist", travel_distance);
  Serial.print("travel_distance: ");
  Serial.println(travel_distance);
  maximum_motor_position = (travel_distance / 1.484252) * 200; //For a 12mm diameter pulley. At 200 steps/revolution
}

void sliderPosition(Control* sender, int type) {
  Serial.println(sender->value);
  target_percent = sender->value.toInt();
  target_position = (maximum_motor_position / 100) * target_percent;
  move_to_percent100ths(target_percent);
  run_motor = true;
}

void buttonSetZeroCall(Control* sender, int type) {
  switch (type) {
    case B_DOWN:
      Serial.println("Button Pressed");
      set_zero = 1;
      Serial.print("set_zero: ");
      Serial.println(set_zero);
      break;
  }
}

void switchChangeDirectionCall(Control* sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("Active");
      opening_direction = 1;
      preferences.putInt("open_dir", opening_direction);
      driver.shaft(true);
      break;

    case S_INACTIVE:
      Serial.print("Inactive");
      opening_direction = 0;
      preferences.putInt("open_dir", opening_direction);
      driver.shaft(false);
      break;
  }
  Serial.print(" ");
  Serial.println(sender->id);
}

void textNetworkCall(Control* sender, int type) {
}

void textPasswordCall(Control* sender, int type) {
}

void buttonSaveNetworkCall(Control* sender, int type) {
  if (type == B_UP) {
    Serial.println("Button Pressed");
    String ssid = ESPUI.getControl(wifi_ssid_text)->value;
    String pass = ESPUI.getControl(wifi_pass_text)->value;
    preferences.putString("ssid", ssid);
    preferences.putString("pass", pass);
    ESP.restart();
  }
}

void buttonClearNetworkCall(Control* sender, int type) {
  if (type == B_UP) {
    preferences.putInt("wifi_set", 0);
    preferences.putString("ssid", "NOT_SET");
    preferences.putString("pass", "NOT_SET");
    preferences.end();
    ESP.restart();
  }
}

void ESPUIsetup() {

  uint16_t tab1 = ESPUI.addControl(ControlType::Tab, "Positioning", "Positioning");
  uint16_t tab2 = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");
  uint16_t tab3 = ESPUI.addControl(ControlType::Tab, "WiFi", "WiFi");
  uint16_t tab4 = ESPUI.addControl(ControlType::Tab, "API", "API");

  // // shown above all tabs. Not part of any tab
  // //status = ESPUI.addControl(ControlType::Label, "Status:", "Stop", ControlColor::Turquoise);

  //Tab1: Positioning
  //Text: Current position percent
  positionLabel = ESPUI.addControl(ControlType::Label, "Current Position", String(target_percent), ControlColor::Turquoise, tab1);
  //Slider: Move to position
  uint16_t positionMax = ESPUI.addControl(ControlType::Slider, "Position", "0", ControlColor::Alizarin, tab1, &sliderPosition);
  ESPUI.addControl(ControlType::Min, "", "0", ControlColor::None, positionMax);
  ESPUI.addControl(ControlType::Max, "", "100", ControlColor::None, positionMax);


  // //Tab2: Settings
  ESPUI.addControl(ControlType::Separator, "Home Position", "", ControlColor::Peterriver, tab2);
  //Button: Set Zero
  ESPUI.addControl(ControlType::Switcher, "Change Direction", String(opening_direction), ControlColor::Dark, tab2, &switchChangeDirectionCall);
  ESPUI.addControl(ControlType::Button, "Set Zero", "Set", ControlColor::Dark, tab2, &buttonSetZeroCall);

  ESPUI.addControl(ControlType::Separator, "Motor Setting", "", ControlColor::Peterriver, tab2);
  //Number: Max Steps
  //ESPUI.addControl(ControlType::Number, "Max Steps:", String(maximum_motor_position), ControlColor::Peterriver, tab2, &numberMaxStepsCall);
   //Number: Max Steps
  ESPUI.addControl(ControlType::Number, "Max Inches:", String(travel_distance), ControlColor::Peterriver, tab2, &numberTravelCall);

  // //Number: Current
  // speedMax = ESPUI.addControl(ControlType::Number, "Speed", String(max_speed), ControlColor::Alizarin, tab2, &numberSpeedCall);
  // accelMax = ESPUI.addControl(ControlType::Number, "Acceleration", String(accel), ControlColor::Alizarin, tab2, &numberAccelCall);
  // uint16_t currentMax = ESPUI.addControl(ControlType::Number, "Current(mA)", String(current), ControlColor::Alizarin, tab2, &numberCurrentCall);
  // ESPUI.addControl(ControlType::Min, "", "400", ControlColor::None, currentMax);
  // ESPUI.addControl(ControlType::Max, "", "2000", ControlColor::None, currentMax);
  // uint16_t stallMax = ESPUI.addControl(ControlType::Number, "Stall", String(stall), ControlColor::Carrot, tab2, &numberStallCall);  //Number: Stall
  // ESPUI.addControl(ControlType::Min, "", "0", ControlColor::None, stallMax);
  // ESPUI.addControl(ControlType::Max, "", "255", ControlColor::None, stallMax);


  //Tab3: WiFi
  ESPUI.addControl(ControlType::Separator, "Set Wifi", "", ControlColor::None, tab3);
  wifi_ssid_text = ESPUI.addControl(ControlType::Text, "Network", String(ssid), ControlColor::Emerald, tab3, &textNetworkCall);        //Text: Network
  wifi_pass_text = ESPUI.addControl(ControlType::Text, "Password", String(password), ControlColor::Emerald, tab3, &textPasswordCall);  //Text: Password
  ESPUI.addControl(ControlType::Button, "Save Settings", "SAVE", ControlColor::Emerald, tab3, &buttonSaveNetworkCall);                 //Button: Save


  // causes CRASH.  Likely IPaddress to string
  //Tab4: API
  // char apiPosition[50];
  // snprintf(apiPosition, sizeof(apiPosition), "http://%s:8080/position?target_percent=%i", WiFi.localIP().toString(), target_percent);
  // ESPUI.addControl(ControlType::Label, "Move to Position", apiPosition, ControlColor::Turquoise, tab4);

  // char apisettings[50];
  // snprintf(apisettings, sizeof(apisettings), "http://%s:8080/settings", WiFi.localIP().toString());
  // ESPUI.addControl(ControlType::Label, "Check Settings", apisettings, ControlColor::Turquoise, tab4);



  ESPUI.sliderContinuous = false;
  ESPUI.begin("Valar Systems");
}
