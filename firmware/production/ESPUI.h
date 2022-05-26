
uint16_t openLabel;
uint16_t closeLabel;
uint16_t labelWifi;
uint16_t wifi_ssid_text, wifi_pass_text;
uint16_t speedMax;
uint16_t accelMax;
String display_wifi;
char openTimeDis[50];
char closeTimeDis[50];


void selectOpenAmPmCall(Control* sender, int value) //Dropdown
{
  if (sender->value == "AM")
  {
    Serial.println(sender->value);
    open_am_pm = 0;
    preferences.putInt("open_am_pm", open_am_pm);
    open_am_pm_s = "AM";
    preferences.putString("open_am_pm_s", open_am_pm_s);

    open_hour = open_hour_input;
    preferences.putInt ("open_hour", open_hour);

    // determine open time
    newOpenTime = makeTime(open_hour, open_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

    // set next time to wakeup
    openEventNow = myTZ.setEvent(scheduleOpen, newOpenTime);


    snprintf(openTimeDis, sizeof(openTimeDis), "%i:%i %s", open_hour, open_minute, open_am_pm_s.c_str());
    ESPUI.updateLabel(openLabel, openTimeDis);

  } else
  {
    Serial.println(sender->value);
    open_am_pm = 1;
    preferences.putInt("open_am_pm", open_am_pm);
    open_am_pm_s = "PM";
    preferences.putString("open_am_pm_s", open_am_pm_s);

    open_hour = open_hour_input + 12;
    preferences.putInt ("open_hour", open_hour);

    // determine open time
    newOpenTime = makeTime(open_hour, open_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

    // set next time to wakeup
    openEventNow = myTZ.setEvent(scheduleOpen, newOpenTime);

    snprintf(openTimeDis, sizeof(openTimeDis), "%i:%i %s", open_hour, open_minute, open_am_pm_s.c_str());
    ESPUI.updateLabel(openLabel, openTimeDis);

  }
}

void selectCloseAmPmCall(Control* sender, int value) //Dropdown
{
  if (sender->value == "AM")
  {
    Serial.println(sender->value);
    close_am_pm = 0;
    preferences.putInt("close_am_pm", close_am_pm);
    close_am_pm_s = "AM";
    preferences.putString("close_am_pm_s", close_am_pm_s);

    close_hour = close_hour_input;
    preferences.putInt ("close_hour", close_hour);

    // determine open time
    newCloseTime = makeTime(close_hour, close_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

    // set next time to wakeup
    closeEventNow = myTZ.setEvent(scheduleClose, newCloseTime);


    snprintf(closeTimeDis, sizeof(closeTimeDis), "%i:%i %s", close_hour, close_minute, close_am_pm_s.c_str());
    ESPUI.updateLabel(closeLabel, closeTimeDis);

  } else
  {
    Serial.println(sender->value);
    close_am_pm = 1;
    preferences.putInt("close_am_pm", close_am_pm);
    close_am_pm_s = "PM";
    preferences.putString("close_am_pm_s", close_am_pm_s);

    close_hour = close_hour_input + 12;
    preferences.putInt ("close_hour", close_hour);

    // determine open time
    newCloseTime = makeTime(close_hour, close_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

    // set next time to wakeup
    closeEventNow = myTZ.setEvent(scheduleClose, newCloseTime);

    snprintf(closeTimeDis, sizeof(closeTimeDis), "%i:%i %s", close_hour, close_minute, close_am_pm_s.c_str());
    ESPUI.updateLabel(closeLabel, closeTimeDis);

  }
}

void selectTimeZoneCall(Control* sender, int value) //Dropdown
{
  Serial.println(sender->value);
  MYTIMEZONE = sender->value;
  preferences.putString("timezone", MYTIMEZONE);
}


void numberMaxStepsCall(Control* sender, int type)
{
  max_steps = sender->value.toInt();
  preferences.putInt ("max_steps", max_steps);
  Serial.print("max_steps: ");
  Serial.println(max_steps);
}

void numberSpeedCall(Control* sender, int type)
{
  max_speed = sender->value.toInt();
  preferences.putInt("max_speed", max_speed);
  stepper->setSpeedInHz(max_speed);
  Serial.print("max_speed: ");
  Serial.println(max_speed);
}

void numberAccelCall(Control* sender, int type)
{
  accel = sender->value.toInt();
  preferences.putInt("accel", accel);
  stepper->setAcceleration(accel);
  Serial.print("accel: ");
  Serial.println(accel);
}

void numberCurrentCall(Control* sender, int type)
{
  current = sender->value.toInt();
  preferences.putInt ("current", current);
  Serial.print("current: ");
  Serial.println(current);
}

void numberStallCall(Control* sender, int type)
{
  Serial.println(sender->value);
  stall = sender->value.toInt();
  driver.SGTHRS(stall);
  preferences.putInt ("stall", stall);
  Serial.print("stall: ");
  Serial.println(stall);
}

void numberOpenHourCall(Control* sender, int type)
{
  Serial.println(sender->value);
  open_hour = sender->value.toInt();
  if (open_hour > 12) open_hour = 12;
  if (open_hour < 1) open_hour = 1;
  open_hour_input = open_hour;

  if (open_am_pm == 1) open_hour = open_hour + 12;

  preferences.putInt ("open_hour", open_hour);
  preferences.putInt ("open_hour_in", open_hour_input);

  // determine open time
  newOpenTime = makeTime(open_hour, open_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

  // set next time to wakeup
  openEventNow = myTZ.setEvent(scheduleOpen, newOpenTime);

  snprintf(openTimeDis, sizeof(openTimeDis), "%i:%i %s", open_hour, open_minute, open_am_pm_s.c_str());
  ESPUI.updateLabel(openLabel, openTimeDis);
}

void numberOpenMinuteCall(Control* sender, int type)
{
  Serial.println(sender->value);
  open_minute = sender->value.toInt();
  if (open_minute > 59) open_minute = 59;
  if (open_minute < 0) open_minute = 0;
  preferences.putInt ("open_minute", open_minute);

  // determine open time
  newOpenTime = makeTime(open_hour, open_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

  // set next time to wakeup
  openEventNow = myTZ.setEvent(scheduleOpen, newOpenTime);

  snprintf(openTimeDis, sizeof(openTimeDis), "%i:%i %s", open_hour, open_minute, open_am_pm_s.c_str());
  ESPUI.updateLabel(openLabel, openTimeDis);
}

void numberCloseHourCall(Control* sender, int type)
{
  Serial.println(sender->value);
  close_hour = sender->value.toInt();
  if (close_hour > 12) close_hour = 12;
  if (close_hour < 1) close_hour = 1;

  close_hour_input = close_hour;
  if (close_am_pm == 1) close_hour = close_hour + 12;

  preferences.putInt ("close_hour", close_hour);
  preferences.putInt ("close_hour_in", close_hour_input);

  // determine close time
  newCloseTime = makeTime(close_hour, close_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

  // set next time to wakeup
  closeEventNow = myTZ.setEvent(scheduleClose, newCloseTime);

  snprintf(closeTimeDis, sizeof(closeTimeDis), "%i:%i %s", close_hour, close_minute, close_am_pm_s.c_str());
  ESPUI.updateLabel(closeLabel, closeTimeDis);
}

void numberCloseMinuteCall(Control* sender, int type)
{
  Serial.println(sender->value);
  close_minute = sender->value.toInt();
  if (close_minute > 59) close_minute = 59;
  if (close_minute < 0) close_minute = 0;
  preferences.putInt ("close_minute", close_minute);

  // determine close time
  newCloseTime = makeTime(close_hour, close_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

  // set next time to wakeup
  closeEventNow = myTZ.setEvent(scheduleClose, newCloseTime);

  snprintf(closeTimeDis, sizeof(closeTimeDis), "%i:%i %s", close_hour, close_minute, close_am_pm_s.c_str());
  ESPUI.updateLabel(closeLabel, closeTimeDis);
}


void sliderPosition(Control* sender, int type)
{
  Serial.println(sender->value);
  move_to_percent = sender->value.toInt();
  move_to_step = (max_steps / 100) * move_to_percent;
  //stepper->moveTo(move_to_step);
  run_motor = true;

}

void buttonSetZeroCall(Control* sender, int type)
{
  switch (type)
  {
    case B_DOWN:
      Serial.println("Button Pressed");
      set_zero = 1;
      Serial.print("set_zero: ");
      Serial.println(set_zero);
      break;
  }
}


void switchChangeDirectionCall(Control* sender, int value)
{
  switch (value)
  {
    case S_ACTIVE:
      Serial.print("Active");
      open_direction = 1;
      preferences.putInt("open_dir", open_direction);
      driver.shaft(true);
      break;

    case S_INACTIVE:
      Serial.print("Inactive");
      open_direction = 0;
      preferences.putInt("open_dir", open_direction);
      driver.shaft(false);
      break;
  }

  Serial.print(" ");
  Serial.println(sender->id);
}

void switchOpenScheduleCall(Control* sender, int value)
{
  switch (value)
  {
    case S_ACTIVE:
      Serial.print("Active");
      open_timer = 1;
      preferences.putInt("open_timer", open_timer);

      // determine open time
      newOpenTime = makeTime(open_hour, open_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

      // set next time to wakeup
      openEventNow = myTZ.setEvent(scheduleOpen, newOpenTime);
      break;

    case S_INACTIVE:
      Serial.print("Inactive");
      open_timer = 0;
      preferences.putInt("open_timer", open_timer);
      deleteEvent(openEvent);
      deleteEvent(openEventNow);
      break;
  }
}

void switchCloseScheduleCall(Control* sender, int value)
{
  switch (value)
  {
    case S_ACTIVE:
      Serial.print("Active");
      close_timer = 1;
      preferences.putInt("close_timer", close_timer);

      // determine open time
      newCloseTime = makeTime(close_hour, close_minute, 0, myTZ.day(), myTZ.month(), myTZ.year());

      // set next time to wakeup
      closeEventNow = myTZ.setEvent(scheduleClose, newCloseTime);
      break;

    case S_INACTIVE:
      Serial.print("Inactive");
      close_timer = 0;
      preferences.putInt("close_timer", close_timer);
      deleteEvent(closeEvent);
      deleteEvent(closeEventNow);
      break;
  }
}

void textNetworkCall(Control* sender, int type)
{
  //    ssid = sender->value;
  //    Serial.print(ssid);

}

void textPasswordCall(Control* sender, int type)
{
  //    Serial.print(sender->value);
  //    pass = sender->value;
  //    Serial.print(pass);
}

void buttonSaveNetworkCall(Control* sender, int type)
{
  if (type == B_UP) {
    Serial.println("Button Pressed");
    ssid = ESPUI.getControl(wifi_ssid_text)->value;
    pass = ESPUI.getControl(wifi_pass_text)->value;
    preferences.putString ("ssid", ssid);
    preferences.putString ("pass", pass);
    wifi_set = 1;
    display_wifi = "SET";
    ESPUI.updateLabel(labelWifi, display_wifi);
    preferences.putInt ("wifi_set", 1);
    connectWifi();
  }
}

void buttonClearNetworkCall(Control* sender, int type)
{
  if (type == B_UP) {
    preferences.putInt ("wifi_set", 0);
    preferences.putString ("ssid", "NOT_SET");
    preferences.putString ("pass", "NOT_SET");
    preferences.end();
    ESP.restart();
  }
}

void ESPUIsetup() {

  uint16_t tab1 = ESPUI.addControl(ControlType::Tab, "Positioning", "Positioning");
  uint16_t tab2 = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");
  uint16_t tab3 = ESPUI.addControl(ControlType::Tab, "Schedule", "Schedule");
  uint16_t tab4 = ESPUI.addControl(ControlType::Tab, "WiFi", "WiFi");
  uint16_t tab5 = ESPUI.addControl(ControlType::Tab, "API", "API");

  // shown above all tabs. Not part of any tab
  //status = ESPUI.addControl(ControlType::Label, "Status:", "Stop", ControlColor::Turquoise);

  //Tab1: Positioning
  //Text: Current position percent
  positionLabel = ESPUI.addControl(ControlType::Label, "Current Position", String(move_to_percent), ControlColor::Turquoise, tab1);
  //Slider: Move to position
  uint16_t positionMax = ESPUI.addControl(ControlType::Slider, "Position", "0", ControlColor::Alizarin, tab1, &sliderPosition);
  ESPUI.addControl(ControlType::Min, "", "0", ControlColor::None, positionMax);
  ESPUI.addControl(ControlType::Max, "", "100", ControlColor::None, positionMax);

  //Tab2: Settings
  ESPUI.addControl(ControlType::Separator, "Home Position", "", ControlColor::Peterriver, tab2);
  //Button: Set Zero
  ESPUI.addControl(ControlType::Switcher, "Change Direction", String(open_direction), ControlColor::Dark, tab2, &switchChangeDirectionCall);
  ESPUI.addControl(ControlType::Button, "Set Zero", "Set", ControlColor::Dark, tab2, &buttonSetZeroCall);

  ESPUI.addControl(ControlType::Separator, "Motor Setting", "", ControlColor::Peterriver, tab2);
  //Number: Max Steps
  ESPUI.addControl(ControlType::Number, "Max Steps:", String(max_steps), ControlColor::Peterriver, tab2, &numberMaxStepsCall);
  //Number: Current
  speedMax = ESPUI.addControl(ControlType::Number, "Speed", String(max_speed), ControlColor::Alizarin, tab2, &numberSpeedCall);
  accelMax = ESPUI.addControl(ControlType::Number, "Acceleration", String(accel), ControlColor::Alizarin, tab2, &numberAccelCall);
  uint16_t currentMax = ESPUI.addControl(ControlType::Number, "Current(mA)", String(current), ControlColor::Alizarin, tab2, &numberCurrentCall);
  ESPUI.addControl(ControlType::Min, "", "400", ControlColor::None, currentMax);
  ESPUI.addControl(ControlType::Max, "", "2000", ControlColor::None, currentMax);
  //Number: Stall
  uint16_t stallMax = ESPUI.addControl(ControlType::Number, "Stall", String(stall), ControlColor::Carrot, tab2, &numberStallCall);
  ESPUI.addControl(ControlType::Min, "", "0", ControlColor::None, stallMax);
  ESPUI.addControl(ControlType::Max, "", "255", ControlColor::None, stallMax);


  //Tab3: Schedule

  //Seperator
  ESPUI.addControl(ControlType::Separator, "Timezone", "", ControlColor::Dark, tab3);

  //Timezone

  //uint16_t timeZoneDrop = ESPUI.addControl(ControlType::Option,"America/Adak", "America_Adak", ControlColor::Carrot, tab3, &selectTimeZoneCall);
  //ESPUI.addControl(ControlType::Option,"America", "America", ControlColor::None, timeZoneDrop);
  //ESPUI.addControl(ControlType::Option,"America_Anguilla", "America_Anguilla", ControlColor::None, timeZoneDrop);

  uint16_t timeZoneDrop = ESPUI.addControl(ControlType::Select, "Time Zone", MYTIMEZONE, ControlColor::Dark, tab3, &selectTimeZoneCall);
  ESPUI.addControl(ControlType::Option, "America/Adak", "America/Adak", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Anchorage", "America/Anchorage", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Anguilla", "America/Anguilla", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Antigua", "America/Antigua", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Araguaina", "America/Araguaina", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Buenos_Aires", "America/Argentina/Buenos_Aires", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Catamarca", "America/Argentina/Catamarca", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/ComodRivadavia", "America/Argentina/ComodRivadavia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Cordoba", "America/Argentina/Cordoba", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Jujuy", "America/Argentina/Jujuy", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/La_Rioja", "America/Argentina/La_Rioja", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Mendoza", "America/Argentina/Mendoza", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Rio_Gallegos", "America/Argentina/Rio_Gallegos", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Salta", "America/Argentina/Salta", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/San_Juan", "America/Argentina/San_Juan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/San_Luis", "America/Argentina/San_Luis", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Tucuman", "America/Argentina/Tucuman", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Argentina/Ushuaia", "America/Argentina/Ushuaia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Aruba", "America/Aruba", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Asuncion", "America/Asuncion", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Atikokan", "America/Atikokan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Atka", "America/Atka", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Bahia", "America/Bahia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Barbados", "America/Barbados", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Belem", "America/Belem", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Belize", "America/Belize", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Blanc-Sablon", "America/Blanc-Sablon", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Boa_Vista", "America/Boa_Vista", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Bogota", "America/Bogota", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Boise", "America/Boise", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Buenos_Aires", "America/Buenos_Aires", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Cambridge_Bay", "America/Cambridge_Bay", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Campo_Grande", "America/Campo_Grande", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Cancun", "America/Cancun", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Caracas", "America/Caracas", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Catamarca", "America/Catamarca", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Cayenne", "America/Cayenne", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Cayman", "America/Cayman", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Chicago", "America/Chicago", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Chihuahua", "America/Chihuahua", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Coral_Harbour", "America/Coral_Harbour", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Cordoba", "America/Cordoba", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Costa_Rica", "America/Costa_Rica", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Cuiaba", "America/Cuiaba", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Curacao", "America/Curacao", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Danmarkshavn", "America/Danmarkshavn", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Dawson", "America/Dawson", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Dawson_Creek", "America/Dawson_Creek", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Denver", "America/Denver", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Detroit", "America/Detroit", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Dominica", "America/Dominica", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Edmonton", "America/Edmonton", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Eirunepe", "America/Eirunepe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/El_Salvador", "America/El_Salvador", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Ensenada", "America/Ensenada", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Fortaleza", "America/Fortaleza", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Fort_Wayne", "America/Fort_Wayne", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Glace_Bay", "America/Glace_Bay", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Godthab", "America/Godthab", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Goose_Bay", "America/Goose_Bay", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Grand_Turk", "America/Grand_Turk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Grenada", "America/Grenada", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Guadeloupe", "America/Guadeloupe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Guatemala", "America/Guatemala", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Guayaquil", "America/Guayaquil", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Guyana", "America/Guyana", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Halifax", "America/Halifax", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Havana", "America/Havana", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Hermosillo", "America/Hermosillo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Indianapolis", "America/Indiana/Indianapolis", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Knox", "America/Indiana/Knox", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Marengo", "America/Indiana/Marengo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Petersburg", "America/Indiana/Petersburg", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Tell_City", "America/Indiana/Tell_City", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Vevay", "America/Indiana/Vevay", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Vincennes", "America/Indiana/Vincennes", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indiana/Winamac", "America/Indiana/Winamac", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Indianapolis", "America/Indianapolis", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Inuvik", "America/Inuvik", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Iqaluit", "America/Iqaluit", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Jamaica", "America/Jamaica", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Jujuy", "America/Jujuy", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Juneau", "America/Juneau", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Kentucky/Louisville", "America/Kentucky/Louisville", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Kentucky/Monticello", "America/Kentucky/Monticello", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Knox_IN", "America/Knox_IN", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/La_Paz", "America/La_Paz", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Lima", "America/Lima", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Los_Angeles", "America/Los_Angeles", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Louisville", "America/Louisville", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Maceio", "America/Maceio", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Managua", "America/Managua", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Manaus", "America/Manaus", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Marigot", "America/Marigot", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Martinique", "America/Martinique", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Matamoros", "America/Matamoros", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Mazatlan", "America/Mazatlan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Mendoza", "America/Mendoza", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Menominee", "America/Menominee", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Merida", "America/Merida", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Mexico_City", "America/Mexico_City", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Miquelon", "America/Miquelon", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Moncton", "America/Moncton", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Monterrey", "America/Monterrey", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Montevideo", "America/Montevideo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Montreal", "America/Montreal", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Montserrat", "America/Montserrat", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Nassau", "America/Nassau", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/New_York", "America/New_York", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Nipigon", "America/Nipigon", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Nome", "America/Nome", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Noronha", "America/Noronha", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/North_Dakota/Center", "America/North_Dakota/Center", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/North_Dakota/New_Salem", "America/North_Dakota/New_Salem", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Ojinaga", "America/Ojinaga", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Panama", "America/Panama", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Pangnirtung", "America/Pangnirtung", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Paramaribo", "America/Paramaribo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Phoenix", "America/Phoenix", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Port-au-Prince", "America/Port-au-Prince", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Porto_Acre", "America/Porto_Acre", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Port_of_Spain", "America/Port_of_Spain", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Porto_Velho", "America/Porto_Velho", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Puerto_Rico", "America/Puerto_Rico", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Rainy_River", "America/Rainy_River", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Rankin_Inlet", "America/Rankin_Inlet", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Recife", "America/Recife", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Regina", "America/Regina", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Resolute", "America/Resolute", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Rio_Branco", "America/Rio_Branco", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Rosario", "America/Rosario", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Santa_Isabel", "America/Santa_Isabel", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Santarem", "America/Santarem", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Santiago", "America/Santiago", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Santo_Domingo", "America/Santo_Domingo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Sao_Paulo", "America/Sao_Paulo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Scoresbysund", "America/Scoresbysund", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Shiprock", "America/Shiprock", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/St_Barthelemy", "America/St_Barthelemy", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/St_Johns", "America/St_Johns", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/St_Kitts", "America/St_Kitts", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/St_Lucia", "America/St_Lucia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/St_Thomas", "America/St_Thomas", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/St_Vincent", "America/St_Vincent", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Swift_Current", "America/Swift_Current", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Tegucigalpa", "America/Tegucigalpa", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Thule", "America/Thule", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Thunder_Bay", "America/Thunder_Bay", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Tijuana", "America/Tijuana", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Toronto", "America/Toronto", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Tortola", "America/Tortola", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Vancouver", "America/Vancouver", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Virgin", "America/Virgin", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Whitehorse", "America/Whitehorse", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Winnipeg", "America/Winnipeg", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Yakutat", "America/Yakutat", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "America/Yellowknife", "America/Yellowknife", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Amsterdam", "Europe/Amsterdam", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Andorra", "Europe/Andorra", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Athens", "Europe/Athens", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Belfast", "Europe/Belfast", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Belgrade", "Europe/Belgrade", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Berlin", "Europe/Berlin", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Bratislava", "Europe/Bratislava", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Brussels", "Europe/Brussels", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Bucharest", "Europe/Bucharest", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Budapest", "Europe/Budapest", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Chisinau", "Europe/Chisinau", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Copenhagen", "Europe/Copenhagen", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Dublin", "Europe/Dublin", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Gibraltar", "Europe/Gibraltar", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Guernsey", "Europe/Guernsey", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Helsinki", "Europe/Helsinki", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Isle_of_Man", "Europe/Isle_of_Man", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Istanbul", "Europe/Istanbul", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Jersey", "Europe/Jersey", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Kaliningrad", "Europe/Kaliningrad", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Kiev", "Europe/Kiev", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Lisbon", "Europe/Lisbon", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Ljubljana", "Europe/Ljubljana", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/London", "Europe/London", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Luxembourg", "Europe/Luxembourg", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Madrid", "Europe/Madrid", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Malta", "Europe/Malta", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Mariehamn", "Europe/Mariehamn", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Minsk", "Europe/Minsk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Monaco", "Europe/Monaco", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Moscow", "Europe/Moscow", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Nicosia", "Europe/Nicosia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Oslo", "Europe/Oslo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Paris", "Europe/Paris", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Podgorica", "Europe/Podgorica", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Prague", "Europe/Prague", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Riga", "Europe/Riga", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Rome", "Europe/Rome", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Samara", "Europe/Samara", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/San_Marino", "Europe/San_Marino", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Sarajevo", "Europe/Sarajevo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Simferopol", "Europe/Simferopol", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Skopje", "Europe/Skopje", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Sofia", "Europe/Sofia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Stockholm", "Europe/Stockholm", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Tallinn", "Europe/Tallinn", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Tirane", "Europe/Tirane", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Tiraspol", "Europe/Tiraspol", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Uzhgorod", "Europe/Uzhgorod", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Vaduz", "Europe/Vaduz", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Vatican", "Europe/Vatican", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Vienna", "Europe/Vienna", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Vilnius", "Europe/Vilnius", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Volgograd", "Europe/Volgograd", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Warsaw", "Europe/Warsaw", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Zagreb", "Europe/Zagreb", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Zaporozhye", "Europe/Zaporozhye", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Europe/Zurich", "Europe/Zurich", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Aden", "Asia/Aden", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Almaty", "Asia/Almaty", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Amman", "Asia/Amman", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Anadyr", "Asia/Anadyr", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Aqtau", "Asia/Aqtau", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Aqtobe", "Asia/Aqtobe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Ashgabat", "Asia/Ashgabat", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Ashkhabad", "Asia/Ashkhabad", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Baghdad", "Asia/Baghdad", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Bahrain", "Asia/Bahrain", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Baku", "Asia/Baku", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Bangkok", "Asia/Bangkok", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Beirut", "Asia/Beirut", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Bishkek", "Asia/Bishkek", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Brunei", "Asia/Brunei", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Calcutta", "Asia/Calcutta", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Choibalsan", "Asia/Choibalsan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Chongqing", "Asia/Chongqing", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Chungking", "Asia/Chungking", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Colombo", "Asia/Colombo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Dacca", "Asia/Dacca", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Damascus", "Asia/Damascus", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Dhaka", "Asia/Dhaka", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Dili", "Asia/Dili", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Dubai", "Asia/Dubai", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Dushanbe", "Asia/Dushanbe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Gaza", "Asia/Gaza", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Harbin", "Asia/Harbin", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Ho_Chi_Minh", "Asia/Ho_Chi_Minh", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Hong_Kong", "Asia/Hong_Kong", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Hovd", "Asia/Hovd", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Irkutsk", "Asia/Irkutsk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Istanbul", "Asia/Istanbul", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Jakarta", "Asia/Jakarta", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Jayapura", "Asia/Jayapura", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Jerusalem", "Asia/Jerusalem", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kabul", "Asia/Kabul", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kamchatka", "Asia/Kamchatka", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Karachi", "Asia/Karachi", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kashgar", "Asia/Kashgar", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kathmandu", "Asia/Kathmandu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Katmandu", "Asia/Katmandu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kolkata", "Asia/Kolkata", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Krasnoyarsk", "Asia/Krasnoyarsk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kuala_Lumpur", "Asia/Kuala_Lumpur", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kuching", "Asia/Kuching", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Kuwait", "Asia/Kuwait", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Macao", "Asia/Macao", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Macau", "Asia/Macau", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Magadan", "Asia/Magadan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Makassar", "Asia/Makassar", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Manila", "Asia/Manila", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Muscat", "Asia/Muscat", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Nicosia", "Asia/Nicosia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Novokuznetsk", "Asia/Novokuznetsk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Novosibirsk", "Asia/Novosibirsk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Omsk", "Asia/Omsk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Oral", "Asia/Oral", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Phnom_Penh", "Asia/Phnom_Penh", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Pontianak", "Asia/Pontianak", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Pyongyang", "Asia/Pyongyang", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Qatar", "Asia/Qatar", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Qyzylorda", "Asia/Qyzylorda", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Rangoon", "Asia/Rangoon", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Riyadh", "Asia/Riyadh", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Saigon", "Asia/Saigon", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Sakhalin", "Asia/Sakhalin", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Samarkand", "Asia/Samarkand", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Seoul", "Asia/Seoul", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Shanghai", "Asia/Shanghai", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Singapore", "Asia/Singapore", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Taipei", "Asia/Taipei", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Tashkent", "Asia/Tashkent", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Tbilisi", "Asia/Tbilisi", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Tehran", "Asia/Tehran", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Tel_Aviv", "Asia/Tel_Aviv", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Thimbu", "Asia/Thimbu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Thimphu", "Asia/Thimphu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Tokyo", "Asia/Tokyo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Ujung_Pandang", "Asia/Ujung_Pandang", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Ulaanbaatar", "Asia/Ulaanbaatar", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Ulan_Bator", "Asia/Ulan_Bator", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Urumqi", "Asia/Urumqi", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Vientiane", "Asia/Vientiane", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Vladivostok", "Asia/Vladivostok", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Yakutsk", "Asia/Yakutsk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Yekaterinburg", "Asia/Yekaterinburg", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Asia/Yerevan", "Asia/Yerevan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Abidjan", "Africa/Abidjan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Accra", "Africa/Accra", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Addis_Ababa", "Africa/Addis_Ababa", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Algiers", "Africa/Algiers", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Asmara", "Africa/Asmara", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Asmera", "Africa/Asmera", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Bamako", "Africa/Bamako", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Bangui", "Africa/Bangui", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Banjul", "Africa/Banjul", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Bissau", "Africa/Bissau", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Blantyre", "Africa/Blantyre", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Brazzaville", "Africa/Brazzaville", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Bujumbura", "Africa/Bujumbura", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Cairo", "Africa/Cairo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Casablanca", "Africa/Casablanca", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Ceuta", "Africa/Ceuta", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Conakry", "Africa/Conakry", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Dakar", "Africa/Dakar", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Dar_es_Salaam", "Africa/Dar_es_Salaam", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Djibouti", "Africa/Djibouti", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Douala", "Africa/Douala", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/El_Aaiun", "Africa/El_Aaiun", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Freetown", "Africa/Freetown", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Gaborone", "Africa/Gaborone", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Harare", "Africa/Harare", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Johannesburg", "Africa/Johannesburg", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Kampala", "Africa/Kampala", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Khartoum", "Africa/Khartoum", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Kigali", "Africa/Kigali", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Kinshasa", "Africa/Kinshasa", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Lagos", "Africa/Lagos", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Libreville", "Africa/Libreville", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Lome", "Africa/Lome", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Luanda", "Africa/Luanda", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Lubumbashi", "Africa/Lubumbashi", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Lusaka", "Africa/Lusaka", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Malabo", "Africa/Malabo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Maputo", "Africa/Maputo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Maseru", "Africa/Maseru", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Mbabane", "Africa/Mbabane", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Mogadishu", "Africa/Mogadishu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Monrovia", "Africa/Monrovia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Nairobi", "Africa/Nairobi", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Ndjamena", "Africa/Ndjamena", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Niamey", "Africa/Niamey", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Nouakchott", "Africa/Nouakchott", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Ouagadougou", "Africa/Ouagadougou", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Porto-Novo", "Africa/Porto-Novo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Sao_Tome", "Africa/Sao_Tome", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Timbuktu", "Africa/Timbuktu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Tripoli", "Africa/Tripoli", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Tunis", "Africa/Tunis", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Africa/Windhoek", "Africa/Windhoek", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/ACT", "Australia/ACT", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Adelaide", "Australia/Adelaide", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Brisbane", "Australia/Brisbane", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Broken_Hill", "Australia/Broken_Hill", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Canberra", "Australia/Canberra", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Currie", "Australia/Currie", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Darwin", "Australia/Darwin", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Eucla", "Australia/Eucla", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Hobart", "Australia/Hobart", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/LHI", "Australia/LHI", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Lindeman", "Australia/Lindeman", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Lord_Howe", "Australia/Lord_Howe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Melbourne", "Australia/Melbourne", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/North", "Australia/North", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/NSW", "Australia/NSW", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Perth", "Australia/Perth", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Queensland", "Australia/Queensland", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/South", "Australia/South", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Sydney", "Australia/Sydney", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Tasmania", "Australia/Tasmania", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Victoria", "Australia/Victoria", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/West", "Australia/West", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Australia/Yancowinna", "Australia/Yancowinna", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Antananarivo", "Indian/Antananarivo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Chagos", "Indian/Chagos", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Christmas", "Indian/Christmas", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Cocos", "Indian/Cocos", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Comoro", "Indian/Comoro", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Kerguelen", "Indian/Kerguelen", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Mahe", "Indian/Mahe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Maldives", "Indian/Maldives", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Mauritius", "Indian/Mauritius", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Mayotte", "Indian/Mayotte", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Indian/Reunion", "Indian/Reunion", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Azores", "Atlantic/Azores", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Bermuda", "Atlantic/Bermuda", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Canary", "Atlantic/Canary", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Cape_Verde", "Atlantic/Cape_Verde", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Faeroe", "Atlantic/Faeroe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Faroe", "Atlantic/Faroe", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Jan_Mayen", "Atlantic/Jan_Mayen", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Madeira", "Atlantic/Madeira", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Reykjavik", "Atlantic/Reykjavik", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/South_Georgia", "Atlantic/South_Georgia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/Stanley", "Atlantic/Stanley", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Atlantic/St_Helena", "Atlantic/St_Helena", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Apia", "Pacific/Apia", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Auckland", "Pacific/Auckland", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Chatham", "Pacific/Chatham", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Easter", "Pacific/Easter", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Efate", "Pacific/Efate", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Enderbury", "Pacific/Enderbury", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Fakaofo", "Pacific/Fakaofo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Fiji", "Pacific/Fiji", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Funafuti", "Pacific/Funafuti", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Galapagos", "Pacific/Galapagos", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Gambier", "Pacific/Gambier", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Guadalcanal", "Pacific/Guadalcanal", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Guam", "Pacific/Guam", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Honolulu", "Pacific/Honolulu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Johnston", "Pacific/Johnston", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Kiritimati", "Pacific/Kiritimati", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Kosrae", "Pacific/Kosrae", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Kwajalein", "Pacific/Kwajalein", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Majuro", "Pacific/Majuro", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Marquesas", "Pacific/Marquesas", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Midway", "Pacific/Midway", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Nauru", "Pacific/Nauru", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Niue", "Pacific/Niue", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Norfolk", "Pacific/Norfolk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Noumea", "Pacific/Noumea", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Pago_Pago", "Pacific/Pago_Pago", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Palau", "Pacific/Palau", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Pitcairn", "Pacific/Pitcairn", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Ponape", "Pacific/Ponape", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Port_Moresby", "Pacific/Port_Moresby", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Rarotonga", "Pacific/Rarotonga", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Saipan", "Pacific/Saipan", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Samoa", "Pacific/Samoa", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Tahiti", "Pacific/Tahiti", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Tarawa", "Pacific/Tarawa", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Tongatapu", "Pacific/Tongatapu", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Truk", "Pacific/Truk", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Wake", "Pacific/Wake", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Wallis", "Pacific/Wallis", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Pacific/Yap", "Pacific/Yap", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Casey", "Antarctica/Casey", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Davis", "Antarctica/Davis", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/DumontDUrville", "Antarctica/DumontDUrville", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Macquarie", "Antarctica/Macquarie", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Mawson", "Antarctica/Mawson", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/McMurdo", "Antarctica/McMurdo", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Palmer", "Antarctica/Palmer", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Rothera", "Antarctica/Rothera", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/South_Pole", "Antarctica/South_Pole", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Syowa", "Antarctica/Syowa", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Antarctica/Vostok", "Antarctica/Vostok", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "Arctic/Longyearbyen", "Arctic/Longyearbyen", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC", "UTC", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-12", "UTC-12", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-11", "UTC-11", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-10", "UTC-10", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-9", "UTC-9", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-8", "UTC-8", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-7", "UTC-7", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-6", "UTC-6", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-5", "UTC-5", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-4", "UTC-4", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-3", "UTC-3", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-2", "UTC-2", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC-1", "UTC-1", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+0", "UTC+0", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+1", "UTC+1", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+2", "UTC+2", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+3", "UTC+3", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+4", "UTC+4", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+5", "UTC+5", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+6", "UTC+6", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+7", "UTC+7", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+8", "UTC+8", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+9", "UTC+9", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+10", "UTC+10", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+11", "UTC+11", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+12", "UTC+12", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+13", "UTC+13", ControlColor::None, timeZoneDrop);
  ESPUI.addControl(ControlType::Option, "UTC+14", "UTC+14", ControlColor::None, timeZoneDrop);

  //Open Schedule
  ESPUI.addControl(ControlType::Separator, "Open Scheduler", "", ControlColor::Dark, tab3);

  //Switch: Turn on open timer
  ESPUI.addControl(ControlType::Switcher, "Open Schedule", String(open_timer), ControlColor::Sunflower, tab3, &switchOpenScheduleCall);
  //Number: Hour
  uint16_t openHourMax = ESPUI.addControl(ControlType::Number, "Open Hour", String(open_hour_input), ControlColor::Sunflower, tab3, &numberOpenHourCall);
  ESPUI.addControl(ControlType::Min, "", "1", ControlColor::None, openHourMax);
  ESPUI.addControl(ControlType::Max, "", "12", ControlColor::None, openHourMax);
  //Number: minute
  uint16_t openMinuteMax = ESPUI.addControl(ControlType::Number, "Open Minute", String(open_minute), ControlColor::Sunflower, tab3, &numberOpenMinuteCall);
  ESPUI.addControl(ControlType::Min, "", "0", ControlColor::None, openMinuteMax);
  ESPUI.addControl(ControlType::Max, "", "59", ControlColor::None, openMinuteMax);
  //Drop Down: AM/PM
  uint16_t openTime = ESPUI.addControl(ControlType::Select, "AM/PM:", open_am_pm_s, ControlColor::Sunflower, tab3, &selectOpenAmPmCall);
  ESPUI.addControl(ControlType::Option, "AM", "AM", ControlColor::None, openTime);
  ESPUI.addControl(ControlType::Option, "PM", "PM", ControlColor::None, openTime);

  //Close Schedule
  ESPUI.addControl(ControlType::Separator, "Close Scheduler", "", ControlColor::Dark, tab3);

  //Switch: Turn off close
  ESPUI.addControl(ControlType::Switcher, "Close Schedule", String(open_timer), ControlColor::Dark, tab3, &switchOpenScheduleCall);
  //Number: Hour
  uint16_t closeHourMax = ESPUI.addControl(ControlType::Number, "Close Hour", String(close_hour_input), ControlColor::Dark, tab3, &numberCloseHourCall);
  ESPUI.addControl(ControlType::Min, "", "1", ControlColor::None, closeHourMax);
  ESPUI.addControl(ControlType::Max, "", "12", ControlColor::None, closeHourMax);
  //Number: minute
  uint16_t closeMinuteMax = ESPUI.addControl(ControlType::Number, "Close Minute", String(close_minute), ControlColor::Dark, tab3, &numberCloseMinuteCall);
  ESPUI.addControl(ControlType::Min, "", "0", ControlColor::None, closeMinuteMax);
  ESPUI.addControl(ControlType::Max, "", "59", ControlColor::None, closeMinuteMax);
  //Drop Down: AM/PM
  uint16_t closeTime = ESPUI.addControl(ControlType::Select, "AM/PM:", close_am_pm_s, ControlColor::Dark, tab3, &selectCloseAmPmCall);
  ESPUI.addControl(ControlType::Option, "AM", "AM", ControlColor::None, closeTime);
  ESPUI.addControl(ControlType::Option, "PM", "PM", ControlColor::None, closeTime);

  //Tab4: WiFi
  ESPUI.addControl(ControlType::Separator, "Wifi Status", "", ControlColor::None, tab4);
  //Label: Is wifi set?


  if (wifi_set)
  {
    display_wifi = "SET";
  } else
  {
    display_wifi = "ACCESS POINT";
  }

  labelWifi = ESPUI.addControl(ControlType::Label, "Wifi Status", display_wifi, ControlColor::Emerald, tab4);
  //Button: Clear Network Settings
  ESPUI.addControl(ControlType::Button, "Clear Settings", "CLEAR", ControlColor::Emerald, tab4, &buttonClearNetworkCall);
  //Text: Name


  ESPUI.addControl(ControlType::Separator, "Set Wifi", "", ControlColor::None, tab4);
  wifi_ssid_text = ESPUI.addControl(ControlType::Text, "Network", ssid, ControlColor::Emerald, tab4, &textNetworkCall);

  //Text: Password
  wifi_pass_text = ESPUI.addControl(ControlType::Text, "Password", "******", ControlColor::Emerald, tab4, &textPasswordCall);

  //Button: Save
  ESPUI.addControl(ControlType::Button, "Save Settings", "SAVE", ControlColor::Emerald, tab4, &buttonSaveNetworkCall);

  //Tab5: API
  char apiPosition[50];
  snprintf(apiPosition, sizeof(apiPosition), "http://%s:8080/position?move_to_percent=%i", ip_address.c_str(), move_to_percent);
  ESPUI.addControl(ControlType::Label, "Move to Position", apiPosition, ControlColor::Turquoise, tab5);

  char apisettings[50];
  snprintf(apisettings, sizeof(apisettings), "http://%s:8080/settings", ip_address.c_str());
  ESPUI.addControl(ControlType::Label, "Check Settings", apisettings, ControlColor::Turquoise, tab5);

  ESPUI.sliderContinuous = false;
  ESPUI.begin("Valar Systems");

}
