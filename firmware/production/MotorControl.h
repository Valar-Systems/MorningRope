#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#define STEP_PIN  13
#define DIR_PIN  14
#define ENABLE_PIN 27
#define BUTTON1 23
#define BUTTON2 34
#define RXD2 16
#define TXD2 17
#define STALLGUARD 2 
#define SENSOR1 32
#define SENSOR2 22

#define SHAFT false

#define SERIAL_PORT_2    Serial2    // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS   0b00       // TMC2209 Driver address according to MS1 and MS2
#define R_SENSE          0.10f      // E_SENSE for current calc.  


AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
TMC2209Stepper driver(&SERIAL_PORT_2, R_SENSE , DRIVER_ADDRESS);

void feedTheDog()
{
  // feed dog 0
  TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE; // write enable
  TIMERG0.wdt_feed = 1;                       // feed dog
  TIMERG0.wdt_wprotect = 0;                   // write protect
}

void IRAM_ATTR button1pressed() 
{
    move_to = 0;
    run_motor = true;
}

void IRAM_ATTR button2pressed() 
{
    move_to = max_steps;
    run_motor = true;
}

void IRAM_ATTR stalled_position()
{
  stalled_motor = true;

}

void IRAM_ATTR sensor_short()
{
  sensor2_trip = true;
}

void IRAM_ATTR sensor_long()
{
  sensor1_trip = true;
}

void IRAM_ATTR wifi_button_press()
{
  wifi_button = true;
}

void setZero()
{
      XACTUAL=0;
      stepper.setCurrentPosition(0);
      Serial.print("XACTUAL: ");
      Serial.println(XACTUAL);
}

void move_motor() {
  Serial.print("Current Position: ");
  Serial.println(XACTUAL);
  
  Serial.print("Moving to Position: ");
  Serial.println(move_to);

  stepper.setCurrentPosition(XACTUAL);
  stepper.moveTo(move_to);
  
  stalled_motor = false;
  sensor1_trip = false;
  sensor2_trip = false;
  
  stepper.setAcceleration(accel);
  stepper.setMaxSpeed(max_speed);
  driver.rms_current(current);
  driver.SGTHRS(stall);
  driver.TCOOLTHRS(tcools);

if(move_to > XACTUAL) // Open
  {

      Serial.println("Opening"); 
      stepper.enableOutputs();
    
      while (stepper.currentPosition() != stepper.targetPosition()) {

      
      if (stalled_motor == true)
      {
        printf("Stalled\n");
        stepper.moveTo(stepper.currentPosition());
      }

      stepper.run();
      feedTheDog();
      }
  }
  else if(move_to < XACTUAL)
  {
  
      Serial.println("Closing");
      stepper.enableOutputs();
    
      while (stepper.currentPosition() != stepper.targetPosition()) 
      {
          if (stalled_motor == true)
          {
            printf("Stalled\n");
            stepper.moveTo(stepper.currentPosition());
          }

      stepper.run();
      feedTheDog();

      }
}
else
{
  Serial.println("DO NOTHING!");
}

      XACTUAL = stepper.currentPosition();
      stepper.disableOutputs();
      printf("Motor Function Complete\n");
}

// put your setup code here, to run once:
void setup_motors(){ 
  
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(STALLGUARD ,INPUT);
  pinMode(WIFI_PIN ,INPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  SERIAL_PORT_2.begin(115200);

  driver.begin();
  driver.toff(4);
  driver.blank_time(24);
  driver.I_scale_analog(false);
  driver.internal_Rsense(false);
  driver.mstep_reg_select(true);
  driver.rms_current(current); 
  driver.SGTHRS(stall);
  driver.microsteps(0);
  driver.TCOOLTHRS(tcools); // 
  driver.TPWMTHRS(0);
  driver.semin(0);
  driver.shaft(true);  
  driver.en_spreadCycle(false);
  driver.pdn_disable(true);

  stepper.setEnablePin(ENABLE_PIN);
  stepper.setPinsInverted(false, false, true);
  stepper.disableOutputs();
  
  attachInterrupt(STALLGUARD, stalled_position, RISING);
  attachInterrupt(WIFI_PIN, wifi_button_press, FALLING);
  attachInterrupt(BUTTON1, button1pressed, FALLING);
  attachInterrupt(BUTTON2, button2pressed, FALLING);
  attachInterrupt(SENSOR1, sensor_long, FALLING);
  attachInterrupt(SENSOR2, sensor_short, FALLING);

}
