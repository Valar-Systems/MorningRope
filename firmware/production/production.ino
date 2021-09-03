/*
 * MODEL-S Curtain Opener
 * By Daniel Frenkel
 */

#include <Arduino.h>
#include <AccelStepper.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>
#include <SPI.h>
#include <Preferences.h>
#include "Memory.h"
#include "ResetButton.h"
#include "MotorControl.h"
#include "API.h"

// define three tasks
void TaskOne( void *pvParameters );
void TaskTwo( void *pvParameters );
void TaskThree( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(115200);
  delay(1000);
  
  preferences.begin("local", false);
  
  load_preferences();
  setup_motors();
  API();
  
  // Now set up tasks to run independently.
  xTaskCreatePinnedToCore(
    MotorTask //Motor Task
    ,  "MotorTask"   // A name just for humans
    ,  1024*4  // This stack size can be checked & adjusted by reading the Stack Highwater
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

void MotorTask(void *pvParameters)  // Motor Task
{
  (void) pvParameters;

  for (;;)
  {
    if(run_motor == true)
    {
      Serial.println("Run Motor Function");
      move_motor();
      run_motor = false;
      Serial.println("Motor Complete");
    }
    else if(set_zero == 1)
    {
      setZero();
      set_zero = 0;
    }
    else if(wifi_button == true)
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
