// define all the pins that are going to be used
int button_pin = 2;
int pot_pin = A0; // set the potentiometer signal pin to A0
int joystick_pin = A1; // set the joystick pin for the x direction to A1

const int num_tasks = 3;
int red_led_pin = 9;
int green_led_pin = 10;
int blue_led_pin = 11;
int led_pins[num_tasks] = {red_led_pin, green_led_pin, blue_led_pin};
int buzzer_pin = 3;

long game_score = 0;

enum game_action {
  BUTTON,
  POTENTIOMETER,
  JOYSTICK,
  NONE
};

game_action task;
int task_number;

long task_timer = 0;
long task_time_limit = 3000;
long task_pause = 300;

int last_pot_value = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println("Starting program...");

  pinMode(button_pin, INPUT_PULLUP);
  pinMode(pot_pin, INPUT);
  pinMode(joystick_pin, INPUT);

  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(blue_led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  randomSeed(analogRead(5));

  task = NONE;
  task_timer = millis();
}

void loop() {
  // Serial.print("Button Value: ");
  // Serial.print(digitalRead(button_pin));
  // Serial.print(" Potentiometer Value ");
  // Serial.print(analogRead(pot_pin));
  // Serial.print(" Joystick Value ");
  // Serial.println(analogRead(joystick_pin));

  // put your main code here, to run repeatedly:
  if (millis() - task_timer > task_time_limit + task_pause) {
    set_new_task();
  } else if (millis() - task_timer > task_time_limit) {
    turn_off_leds();
  } else {
    check_user_action();
  }
}

void turn_off_leds() {
  for (int i = 0; i < num_tasks; i++) {
    digitalWrite(led_pins[i], LOW);
  }

}

void set_new_task() {
  task = random(num_tasks);

  digitalWrite(led_pins[task], HIGH);

  Serial.println();
  Serial.print("Your score: ");
  Serial.println(game_score);

  Serial.print("Selecting new task ");
  Serial.println(task);

  noTone(buzzer_pin);
  task_timer = millis();

  if (task == POTENTIOMETER) {
    last_pot_value = analogRead(pot_pin);
  }
}

bool check_user_action() {
  if (task == BUTTON) {
    int button_value = digitalRead(button_pin);
    if (button_value == LOW) {
      game_score += 5;
      tone(buzzer_pin, 440);
      task_timer = millis() - task_time_limit + 1;
    }
  } else if (task == POTENTIOMETER) {
    int pot_value = analogRead(pot_pin);

    if ((last_pot_value < 512 && pot_value > 700) ||
        (last_pot_value > 512 && pot_value < 300)) {
      game_score += 7;
      tone(buzzer_pin, 494);
      task_timer = millis() - task_time_limit + 1;
    }
  } else if (task == JOYSTICK) {
    int joystick_value = analogRead(joystick_pin);

    if (joystick_value > 900) {
      game_score += 10;
      tone(buzzer_pin, 523);
      task_timer = millis() - task_time_limit + 1;
    }
  }
}