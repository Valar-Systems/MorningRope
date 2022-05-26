#include <Arduino.h>
#include <ESPUI.h>
#include <ezTime.h>
#include "FastAccelStepper.h"
#include <HardwareSerial.h>
#include <TMCStepper.h>
#include <SPI.h>
#include <Preferences.h>
#include "Memory.h"
#include "ResetButton.h"
#include "MotorControl.h"
#include "API.h"
#include "ESPUI.h"

void setup() {

  Serial.begin(115200);
  delay(1000);
  preferences.begin("local", false);
  load_preferences();
  setup_motors();
  setup_leds();
  API();
  ESPUIsetup();

  // Now set up tasks to run independently.
  xTaskCreatePinnedToCore(
    MotorTask //Motor Task
    ,  "MotorTask"   // A name just for humans
    ,  1024 * 4 // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL
    ,  1);

  xTaskCreatePinnedToCore(
    ButtonTask //Motor Task
    ,  "ButtonTask"   // A name just for humans
    ,  1024 * 4 // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL
    ,  0);
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void ButtonTask(void *pvParameters)  // Motor Task
{
  (void) pvParameters;

  for (;;)
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

      //Fade instead of turn off
      if (brightness0 > 255) {
        brightness0 = 255;
        fade0Amount = -fade0Amount;
      }

      if (brightness0 < 0) {

        brightness0 = 0;
        ledcWrite(0, brightness0);
        btn1Press = 0;
        fade0Amount = 15;
        motorRunning = false;
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

      if (brightness1 <= 255 && brightness1 >= 0) {
        ledcWrite(1, brightness1); // set the brightness of the LED
        brightness1 = brightness1 + fade1Amount;
        vTaskDelay(30);
      }

      //Fade instead of turn off
      if (brightness1 > 255) {
        brightness1 = 255;
        fade1Amount = -fade1Amount;
      }

      if (brightness1 < 0) {

        brightness1 = 0;
        ledcWrite(1, brightness1);
        btn2Press = 0;
        fade1Amount = 15;
        motorRunning = false;
      }
    }

    else
    {
      vTaskDelay(1);
    }
  }
}

void MotorTask(void *pvParameters)  // Motor Task
{
  (void) pvParameters;

  for (;;)
  {

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
