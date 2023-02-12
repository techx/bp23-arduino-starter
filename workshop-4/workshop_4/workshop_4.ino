// define all the pins that are going to be used
int button_pin = 2;
int pot_pin = A0; // set the potentiometer signal pin to A0
int joystick_x_pin = A1; // set the joystick pin for the x direction to A1
int joystick_y_pin = A2; // set the joystick pin for the y direction to A2

int num_leds = 3;
int red_led_pin = 9;
int green_led_pin = 10;
int blue_led_pin = 11;
int led_pins[num_leds] = {red_led_pin, };

int game_score = 0;

enum game_action {
  BUTTON,
  POTENTIOMETER,
  JOYSTICK_X,
  JOYSTICK_Y
};

game_action task;
int task_number;

int task_timer;
int task_time_limit = 3000;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println("Starting program...");

  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(blue_led_pin, OUTPUT);

  pinMode(button_pin, INPUT_PULLUP);
  pinMode(pot_pin, INPUT);
  pinMode(joystick_x_pin, INPUT);
  pinMode(joystick_y_pin, INPUT);

  randomSeed(analogRead(5));
}

void set_new_task() {
  task_number = random(3);
  for (int i = 0; i < num_leds; i++) {
    digitalWrite(led_pins[task_number], LOW);
  }
  digitalWrite(led_pins[task_number], HIGH);
}

bool check_user_action(int task_number) {
  if (millis() - task_timer > task_time_limit) {
    return false;
  } else {
    if (task_number == BUTTON) {
      int button_value = digitalRead(button_pin);
      if (button_value == HIGH) {
        game_action_task += 5;
        return true;
      }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  task_number = random(3);

  
  

  if (task_number == BUTTON) {

  } else if (task_number == POTENTIOMETER) {

  } else if (task_number == JOYSTICK_X) {

  } else if (task_number == JOYSTICK_y) {

  }
}
