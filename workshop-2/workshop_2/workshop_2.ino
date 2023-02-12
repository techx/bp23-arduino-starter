#include <NewPing.h> // include the ultrasonic sensor library

// define all the pins that are going to be usedran
int pot_pin = A0; // set the potentiometer signal pin to A0
int joystick_x_pin = A1; // set the joystick pin for the x direction to A1
int joystick_y_pin = A2; // set the joystick pin for the y direction to A2
int joystick_btn_pin = 7; // set the joystick pin for the button direction to 7

int ultrasonic_trigger_pin = 9; // set the ultrasonic sensor trigger pin to 9
int ultrasonic_echo_pin = 10; // set the ultrasonic sensor echo pin to 10
int max_ultrasonic_distance_cm = 400; // set the maximum measureable distance for the ultrasonic sensor to 400cm 
NewPing sonar(ultrasonic_trigger_pin, ultrasonic_echo_pin, max_ultrasonic_distance_cm); // create a new ultrasonic sonar object based on the specified settings

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // start the serial at a baud rate of 115200
  Serial.println("Starting program...");

  pinMode(pot_pin, INPUT); // configure the potentiometer pin for input
  pinMode(joystick_x_pin, INPUT); // configure the joystick pin for the x direction for input
  pinMode(joystick_y_pin, INPUT); // configure the joystick pin for the y direction for input
  pinMode(joystick_btn_pin, INPUT_PULLUP); // configure the joystick button pin for input pullup (makes button values more stable)
}

void loop() {
  // put your main code here, to run repeatedly:

  int pot_value = analogRead(pot_pin); // read the analog value going into the potentiometer pin
  int mapped_pot_value = map(pot_value, 0, 1023, 0, 255); // rescale the potentiometer value from 0 - 1023 down to 0 - 255

  int joystick_x_value = analogRead(joystick_x_pin); // read the analog value going into the joystick pin for the x direction
  int joystick_y_value = analogRead(joystick_y_pin); // read the analog value going into the joystick pin for the y direction
  int joystick_sw_value = digitalRead(joystick_btn_pin); // read the digital value going into the joystick button pin

  int ultrasonic_distance_cm = sonar.ping_cm(); // read the distance in cm going to the ultrasonic sensor 

  // print the potentiometer values to the serial
  Serial.print("Pot: ");
  Serial.print(pot_value);
  Serial.print(", ");
  Serial.print(mapped_pot_value);
  
  Serial.print(" Joystick: ");
  Serial.print(joystick_x_value);
  Serial.print(", ");
  Serial.print(joystick_y_value);
  Serial.print(", ");
  Serial.print(joystick_btn_pin);

  Serial.print(" Ultrasonic: ");
  Serial.print(ultrasonic_distance_cm);

  Serial.println();
}
