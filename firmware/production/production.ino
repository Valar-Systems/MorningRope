#include <Arduino.h>
#include <ESPUI.h>
#include <ezTime.h>

#include <TMCStepper.h>
#include <Preferences.h>
#include "Memory.h"
#include "ResetButton.h"
#include "MotorControl.h"
#include "API.h"
#include <EEPROM.h>

void setup() {

  Serial.begin(115200);
  delay(1000);
  preferences.begin("local", false);
  load_preferences();
  setup_motors();
  setup_leds();
  API();
  ESPUIsetup();

void loop()
{

    if (btn1Press == 1) {

      button1Timer = millis();
      waitButton2Timer = millis() + 1000;

      if (millis() < waitButton2Timer && btn2Press == 1 && motorRunning == false) {
        Serial.println("START MOTOR CLOSE");
        motorRunning = true;
        
        if (run_motor == true && move_to_step == max_steps){
          stepper->forceStop();
          move_to_step = 0;
          stepper->moveTo(move_to_step);
          }
        
        else if(run_motor == true && move_to_step == 0 )
        {
          stepper->forceStop();
          delay(100);
          move_to_step = stepper->getCurrentPosition();
          stepper->moveTo(move_to_step);
        }
        else
          {
        move_to_step = 0;
        run_motor = true;
          }
        }
      
      

      if (brightness0 <= 255 && brightness0 >= 0) {
        ledcWrite(0, brightness0); // set the brightness of the LED
        brightness0 = brightness0 + fade0Amount;
        vTaskDelay(30);
      }

    }

    if (btn2Press == 1) {
      button2Timer = millis();
      waitButton1Timer = millis() + 1000;

      if (millis() < waitButton1Timer && btn1Press == 1 && motorRunning == false ) {
        Serial.println("START MOTOR OPEN");
        motorRunning = true;
        
        if (run_motor == true && move_to_step == 0){
          stepper->forceStop();
          move_to_step = max_steps;
          stepper->moveTo(move_to_step);
          }
        
        else if(run_motor == true && move_to_step == max_steps )
        {
          stepper->forceStop();
          delay(100);
          move_to_step = stepper->getCurrentPosition();
          stepper->moveTo(move_to_step);
        }
        else
          {
        move_to_step = max_steps;
        run_motor = true;
          }
        }

    }

    else
    {
      vTaskDelay(1);
    }
  }
}


    if (run_motor == true)
    {
      Serial.println("Run Motor Function");
      move_motor();
      run_motor = false;
      ESPUI.updateLabel(positionLabel, String(int(((float)current_position / (float)max_steps) * 100)));
      Serial.println("Motor Complete");
    }
    else if (set_zero == 1)
    {
      setZero();
      set_zero = 0;
    }
    else if (wifi_button == true)
    {
      button_change();
      wifi_button = false;
    }
    else
    {
      vTaskDelay(1);
    }
  }
}
