uint16_t positionLabel;

#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#define ENABLE_PIN 8
#define BUTTON_1_PIN 3
#define BUTTON_2_PIN 4
#define BUTTON_WIFI_PIN 7
#define RXD2 5
#define TXD2 6

#define STALLGUARD_PIN 1
#define INDEX_PIN 0

#define DRIVER_ADDRESS 0b00  // TMC2209 Driver address according to MS1 and MS2
#define R_SENSE 0.11f        // R_SENSE for current calc.

#define CLOSE_VELOCITY 1200
#define OPEN_VELOCITY -1200
#define STOP_MOTOR_VELOCITY 0


int brightness0 = 0;   // how bright the LED is
int brightness1 = 0;   // how bright the LED is
int fade0Amount = 15;  // how many points to fade the LED by
int fade1Amount = 15;

int button1Timer;
int button2Timer;
int waitButton1Timer;
int waitButton2Timer;
bool motorRunning;

int btn1Press;
int btn2Press;

int allowButtonTime;

TMC2209Stepper driver(&Serial1, R_SENSE, DRIVER_ADDRESS);


void IRAM_ATTR button1pressed() {
  //move_to_step = 0;
  //run_motor = true;
  btn1Press = 1;
}

void IRAM_ATTR button2pressed() {
  //move_to_step = max_steps;
  //run_motor = true;
  btn2Press = 1;
}

void IRAM_ATTR stalled_position() {
  stalled_motor = true;
  stop_motor = true;
}

void IRAM_ATTR wifi_button_press() {
  wifi_button = true;
}

// Interrupt tracks the position of the stepper motor using the index pin
void IRAM_ATTR index_interrupt(void) {

  if is_closing)
    {
      motor_position++;
    }
  else {
    motor_position--;
  }

  // Ensure motor position stays within bounds
  if (motor_position < 0) {
    motor_position = 0;
  } else if (motor_position > max_motor_position) {
    motor_position = max_motor_position;
  }

  // Update the step index
  current_position = motor_position;
}

int getCurrentPosition(){

  return current_position;
}

/* Enables power stage of TMC */
void enable_driver() {
  digitalWrite(ENABLE_PIN, 0);
}

/* Disabled power stage of TMC */
void disable_driver() {
  digitalWrite(ENABLE_PIN, 1);
}


void setZero() {
  current_position = 0;
  stepper->setCurrentPosition(0);
  Serial.print("current_position: ");
  Serial.println(current_position);
  ESPUI.updateLabel(positionLabel, String(current_position));
}

void goHome() {
  current_position = 0;
  move_to_step = -10000;
  run_motor = true;
}

/* Function that commands motor to move to position */
esp_err_t sliding_window::move_to_percent100ths(uint16_t percent100ths, bool ignoreStall) {
  ESP_LOGE(TAG, "move_to_percent100ths(): %i", percent100ths);

  switch (percent100ths) {
    case 0:
      target_position = 0;
      break;
    case 10000:
      target_position = maximum_motor_position;
      break;
    default:
      target_position = (percent100ths / 10000.0) * maximum_motor_position;
      break;
  }

  // Only use target steps if calibrated
  if (target_position == motor_position) {
    ESP_LOGE(TAG, "Not moving the window because it is already at the desired position");
    ESP_LOGE(TAG, "target_position: %li", target_position);
    ESP_LOGE(TAG, "motor_position: %li", motor_position);
    return ESP_ERR_INVALID_STATE;
  } else if (target_position > motor_position || percent100ths == 10000) {
    if (gpio_get_level(CLOSE_LIMIT_SWITCH_PIN) == LIMIT_SWITCH_PRESSED) {
      ESP_LOGE(TAG, "Can't move the window because it is already closed");
      return ESP_ERR_INVALID_STATE;
    }
    move_close();
  } else if (target_position < motor_position || percent100ths == 0) {
    if (gpio_get_level(OPEN_LIMIT_SWITCH_PIN) == LIMIT_SWITCH_PRESSED) {
      ESP_LOGE(TAG, "Can't move the window because it is already open");
      return ESP_ERR_INVALID_STATE;
    }
    move_open();
  }
  return ESP_OK;
}

void sliding_window::move_close() {
  printf("move_close()");

  if (motor_position < 0) {
    motor_position = 0;
  }

  printf(TAG, "motor_position open: %lu", motor_position);  // TESTING

  stop_flag = false;
  is_closing = true;
  is_moving = true;

  // Reset the close retry counter when starting a new close operation
  close_retry_count = 0;

  enable_driver();

  printf("starting_step_index: %u", starting_step_index);  // TESTING
  printf("step_index: %u", step_index);                    // TESTING

  // printf("VACTUAL: %lu", driver.VACTUAL()); // TESTING
  // printf("semin: %i", driver.semin());      // TESTING
  // printf("ihold: %i", driver.ihold());      // TESTING
  // printf("ihold: %i", driver.irun());       // TESTING

  driver.VACTUAL(CLOSE_VELOCITY);

  // while position_watcher == false
  while (position_watcher() == false) {
    delay(100);
  }
}

void sliding_window::move_open() {
  printf("move_open()");

  if (motor_position < 0) {
    motor_position = maximum_motor_position;
  }

  printf("motor_position open: %lu", motor_position);  // TESTING

  stop_flag = false;
  is_closing = false;
  is_moving = true;

  enable_driver();

  starting_step_index = step_index;  // What does this do?

  printf("starting_step_index: %u", starting_step_index);  // TESTING
  printf("step_index: %u", step_index);                    // TESTING

  driver.VACTUAL(OPEN_VELOCITY);

  // while position_watcher == false
  while (position_watcher() == false) {
    delay(100);
  }
}

// User return statement?
bool position_watcher() {

  // Check for stop flag //
  if (stop_flag == true) {
    stop();
    stop_flag = false;
    printf("position_watcher_task: stop_flag == true");

    return true;
  }

  // /* Check if Position reached */
  if (target_position != maximum_motor_position && target_position != 0) {
    if (is_closing) {
      if (target_position <= motor_position) {
        printf("position_watcher_task STOPPING because target_position: %u <= motor_position: %u", (unsigned int)target_position, (unsigned int)motor_position);
        stop();
        if (motor_position >= maximum_motor_position)
          motor_position = maximum_motor_position;
        return true;
      }
    } else {
      if (target_position >= motor_position) {
        printf("position_watcher_task STOPPING because target_position: %u >= motor_position: %u", (unsigned int)target_position, (unsigned int)motor_position);
        stop();
        if (motor_position >= 2147483647)
          motor_position = 0;
        return true;
      }
    }
  }

  return false;
}

/* Stops motor */
void stop() {
  disable_driver();
  printf("stop(): disable_driver");
  driver.VACTUAL(STOP_MOTOR_VELOCITY);
  printf("stop(): driver.VACTUAL(STOP_MOTOR_VELOCITY)");
}

// put your setup code here, to run once:
void setup_motors() {

  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(STALLGUARD_PIN, INPUT);
  pinMode(INDEX_PIN, INPUT);
  pinMode(BUTTON_WIFI_PIN, INPUT);
  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);


  // driver.begin();
  // driver.toff(4);
  // driver.blank_time(24);
  // driver.I_scale_analog(false);
  // driver.internal_Rsense(false);
  // driver.mstep_reg_select(true);
  // driver.rms_current(current);
  // driver.SGTHRS(stall);
  // driver.mres(8);
  // driver.TCOOLTHRS(tcools);  //
  // driver.TPWMTHRS(0);
  // driver.semin(0);

  if (open_direction == 1) {
    driver.shaft(true);
  } else {
    driver.shaft(false);
  }

  // driver.en_spreadCycle(false);
  // driver.pdn_disable(true);

  /* General Registers */
  driver.I_scale_analog(false);
  driver.internal_Rsense(false);
  driver.en_spreadCycle(false);
  driver.index_otpw(false);
  driver.index_step(true);
  driver.pdn_disable(true);
  driver.mstep_reg_select(true);
  driver.multistep_filt(true);

  // NODECONF Registers
  driver.senddelay(6);

  // Factory Registers
  driver.ottrim(0);

  // Velocity Dependent Control
  driver.ihold(0);
  driver.iholddelay(1);  // Set I_HOLD_DELAY to 1 to 15 for smooth standstill current decay
  driver.TPOWERDOWN(20);
  driver.TPWMTHRS(0);
  driver.VACTUAL(0);

  driver.irun(20);       // 27 for 24V // 20 for 12V
  driver.TCOOLTHRS(80);  // TESTING. 20 to turn off coolstep to test vibrations//600 ok//
  // TSTEP = 163 at 400 velocity
  // 54 at 1200 velocity
  // 200 is min SG_RESULT
  // SG_RESULT=
  // SGTHRS = SG_RESULT/2
  driver.SGTHRS(120);  // 100 ok
  // Once SGTHRS has been determined, use 1/16*SGTHRS+1
  // as a starting point for SEMIN.

  // Working values
  // SGTHRS = 100 / semin = 5 // not great, sometimes skips
  // 120/6 working great

  driver.semin(6);  // 6 is great. 5 causes skipped steps. Sometimes 6, always 7 causes current to remain high.
  driver.seup(0);   // 0 works great

  driver.semax(0);  // 0-15 // 0 to 2 recommended
  driver.sedn(0);
  driver.seimin(1);

  // CHOPCONF – Chopper Configuration
  driver.diss2vs(0);
  driver.diss2g(0);
  driver.dedge(0);
  driver.intpol(1);
  /* ERROR: Actual value is 8 microsteps and 1600 msteps/revolution. Not sure why. Could be related to index counting*/
  driver.mres(8);  // 0 = FULLSTEP mode. 200 pulses per revolution.
  driver.vsense(0);
  driver.tbl(2);
  driver.hend(0);
  driver.hstrt(4);
  driver.toff(5);

  // PWMCONF – Voltage PWM Mode StealthChop
  driver.pwm_lim(12);
  driver.pwm_reg(8);    // Try 2
  driver.freewheel(1);  // 1= Freewheel mode. 3 = Coil Short HS. Only short the coil when motor is NOT moving. Use for physical security
  driver.pwm_autograd(1);
  driver.pwm_autoscale(1);
  driver.pwm_freq(1);
  driver.pwm_grad(PWM_grad);  // Test different initial values. Use scope.
  driver.pwm_ofs(36);

  attachInterrupt(STALLGUARD_PIN, stalled_position, RISING);
  attachInterrupt(INDEX_PIN, button2pressed, RISING);
  attachInterrupt(BUTTON_WIFI_PIN, wifi_button_press, FALLING);
  attachInterrupt(BUTTON_1_PIN, button1pressed, FALLING);
  attachInterrupt(BUTTON_2_PIN, button2pressed, FALLING);
}