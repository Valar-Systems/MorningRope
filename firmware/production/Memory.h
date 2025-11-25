#include <Preferences.h>

bool stall_flag = false;

bool stop_motor = false;
bool opening_direction;

int travel_distance;
float diameter_pulley_cm = 1.2f;  // Only change the value if updating the pulley size


float diameter_pulley_in = diameter_pulley_cm * 0.3937f;
float circumference_cm = diameter_pulley_cm * PI;
float circumference_in = diameter_pulley_in * PI;

int current;
int stall;
int accel;
int max_speed;
int tcools = (3089838.00 * pow(float(max_speed), -1.00161534)) * 1.5;
int motor_microsteps = 64;

int set_zero = 0;  // Set to 1 to set home position
bool run_motor = false;

bool is_cm;

bool is_closing;
bool is_moving = false;
bool stop_flag = false;
bool overtemp_flag = false;
;

uint8_t PWM_grad;
uint32_t target_position;
int32_t motor_position;
uint32_t maximum_motor_position = 200;
uint8_t target_percent;

int wifi_set;
bool wifi_button = false;

String ssid;
String password;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);


// Filter anti-rebond (debouncer)
#define DEBOUNCE_TIME 250
volatile uint32_t DebounceTimer = 0;

Preferences preferences;

void load_preferences() {

  Serial.println("LOADING PREFERENCES");

  wifi_set = preferences.getInt("wifi_set", 0);
  ssid = preferences.getString("ssid", "NOT_SET");
  password = preferences.getString("pass", "NOT_SET");
  maximum_motor_position = preferences.getInt("max_motor_pos", 200);
  motor_position = preferences.getInt("motor_pos", 0);
  current = preferences.getLong("current", 1000);
  stall = preferences.getInt("stall", 10);
  accel = preferences.getInt("accel", 10000);
  max_speed = preferences.getInt("max_speed", 30000);
  opening_direction = preferences.getInt("open_dir", 0);
  is_cm = preferences.getInt("is_cm", 0);
  travel_distance = preferences.getInt("travel_dist", 20);
  target_percent = ((float)motor_position / (float)maximum_motor_position) * 100;

  Serial.println("FINISHED LOADING PREFERENCES");
}
