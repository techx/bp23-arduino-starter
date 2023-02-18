// define all the pins that are going to be used
int red_led_pin = 9; // set the output signal pin for the red LED to 9
int green_led_pin = 10; // set the output signal pin for the green LED to 10
int blue_led_pin = 11; // set the output signal pin for the blue LED to 11
// put the LED pins in an array so they can be iterated through for shorter/cleaner code
int led_pins[3] = {red_led_pin, green_led_pin, blue_led_pin}; 

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

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200); // start the serial at a baud rate of 115200
  Serial.println("Starting program...");

  pinMode(red_led_pin, OUTPUT); // configure the red LED pin for output
  pinMode(green_led_pin, OUTPUT); // configure the green LED pin for output
  pinMode(blue_led_pin, OUTPUT); // configure the blue LED pin for output

  randomSeed(analogRead(5)); // initialize the random number generator with arbitrary data noise from a digital pin

  task = NONE; // initialize the first task to no task
  task_timer = millis(); // set the timer to the current time in milliseconds
}

void loop() {
  // put your main code here, to run repeatedly:

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

  task_timer = millis(); // reset the game timer to now, so that any time measurement is in reference to the time a task was assigned
}