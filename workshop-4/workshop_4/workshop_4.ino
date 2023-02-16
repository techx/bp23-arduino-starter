// define all the pins that are going to be used
int button_pin = 2; // set the button signal pin to 2
int pot_pin = A0; // set the potentiometer signal pin to A0
int joystick_pin = A1; // set the joystick pin for the x direction to A1

int red_led_pin = 9; // set the output signal pin for the red LED to 9
int green_led_pin = 10; // set the output signal pin for the green LED to 10
int blue_led_pin = 11; // set the output signal pin for the blue LED to 11
// put the LED pins in an array so they can be iterated through for shorter/cleaner code
int led_pins[num_tasks] = {red_led_pin, green_led_pin, blue_led_pin}; 
int buzzer_pin = 3; // set the output signal pin for the buzzer to 3

// game settings
const int num_tasks = 3; // set the number of tasks to 3
long game_score = 0; // set the player's game score to 0

// define an enum of certain game actions the player needs to do:
// press a button, twist a potentiometer, push a joystick, or none
enum game_action {
  BUTTON,
  POTENTIOMETER,
  JOYSTICK,
  NONE
};
game_action task;

long task_timer = 0; // variable to keep track of how much time has elapsed
long task_time_limit = 3000; // set the amount of time a player has to complete the task (3000 milliseconds = 3 seconds)
long task_pause = 300; // set the amount of pause time between tasks (300 milliseconds = 0.3 seconds)

// variable to keep track of last potentiometer value, 
// so game can keep track of when the current value changes enough to indicate player had twisted potentiometer
int last_pot_value = 0; 

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200); // start the serial at a baud rate of 115200
  Serial.println("Starting program...");

  pinMode(button_pin, INPUT_PULLUP); // configure the button pin for input pullup (makes button values more stable)
  pinMode(pot_pin, INPUT); // configure the potentiometer pin for input
  pinMode(joystick_pin, INPUT); // configure the joystick pin for input

  pinMode(red_led_pin, OUTPUT); // configure the red LED pin for output
  pinMode(green_led_pin, OUTPUT); // configure the green LED pin for output
  pinMode(blue_led_pin, OUTPUT); // configure the blue LED pin for output
  pinMode(buzzer_pin, OUTPUT); // configure the buzzer pin for output

  randomSeed(analogRead(5)); // initialize the random number generator with arbitrary data noise from a digital pin

  task = NONE; // initialize the first task to no task
  task_timer = millis(); // set the timer to the current time in milliseconds
}

void loop() {
  // put your main code here, to run repeatedly:

  // debug all your input values, uncomment this block if you need to debug this
  // Serial.print("Button Value: ");
  // Serial.print(digitalRead(button_pin));
  // Serial.print(" Potentiometer Value ");
  // Serial.print(analogRead(pot_pin));
  // Serial.print(" Joystick Value ");
  // Serial.println(analogRead(joystick_pin));

  // main game state check
  if (millis() - task_timer > task_time_limit + task_pause) {
    // if the time elapsed (current time in milliseconds minus the last stored time) is more than 
    // the time allocated for a task and the time for a pause between tasks, give the player a new one
    set_new_task();
  } else if (millis() - task_timer > task_time_limit) {
    // if the time elapsed (current time in milliseconds minus the last stored time) is more than 
    // the time allocated for a task, turn off the LEDs
    turn_off_leds();
  } else {
    // otherwise, if the time for a task hasn't expired, check if the user has completed the task
    check_user_action();
  }
}

void turn_off_leds() {
  // iterate through all the LEDs and shut them off
  for (int i = 0; i < num_tasks; i++) {
    digitalWrite(led_pins[i], LOW);
  }
}

void set_new_task() {
  task = random(num_tasks); // set the task to a random number between 0 and num_tasks - 1 (3 - 1 = 2)
  digitalWrite(led_pins[task], HIGH); // turn on the LED corresponding to that task

  // print the user's score and the new task to Serial
  Serial.println();
  Serial.print("Your score: ");
  Serial.println(game_score);
  Serial.print("Selecting new task ");
  Serial.println(task);

  noTone(buzzer_pin); // shut off the buzzer
  task_timer = millis(); // reset the game timer to now, so that any time measurement is in reference to the time a task was assigned

  // if the assigned task is to twist a potentiometer, measure the current value of the potentiometer so when the player twists it 
  // to a new value, it can be measured against the last value
  if (task == POTENTIOMETER) {
    last_pot_value = analogRead(pot_pin);
  }
}

bool check_user_action() {
  // check if the user has completed a certain task, and give them points
  if (task == BUTTON) {
    // check if the button has been pressed
    int button_value = digitalRead(button_pin); // read 
    if (button_value == LOW) { // since the button pin is set to INPUT_PULLUP, so LOW means pressed and HIGH means released
      game_score += 5; // add 5 points to the player's game score
      tone(buzzer_pin, 440); // play an A4 note on the buzzer

      task_timer = millis() - task_time_limit + 1; // reset the task timer so that no more time is left for the task
    }
  } else if (task == POTENTIOMETER) {
    // check if the potentiometer has been twisted
    int pot_value = analogRead(pot_pin);

    // if the potentiometer's last value was turned past the midpoint one way, check if it was twisted past the midpoint the other way
    if ((last_pot_value < 512 && pot_value > 700) ||
        (last_pot_value > 512 && pot_value < 300)) {
      game_score += 7; // add 7 points to the player's game score
      tone(buzzer_pin, 494); // play a B4 note on the buzzer
      task_timer = millis() - task_time_limit + 1; // reset the task timer so that no more time is left for the task
    }
  } else if (task == JOYSTICK) {
    // check if the joystick has been pushed
    int joystick_value = analogRead(joystick_pin);

    // if the joystick value has been pushed far enough, the task is done
    if (joystick_value > 900) {
      game_score += 10; // add 10 points to the player's game score
      tone(buzzer_pin, 523); // play an C4 note on the buzzer

      task_timer = millis() - task_time_limit + 1; // reset the task timer so that no more time is left for the task
    }
  }
}