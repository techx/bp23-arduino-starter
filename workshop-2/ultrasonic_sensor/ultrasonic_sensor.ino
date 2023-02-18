#include <NewPing.h> // include the ultrasonic sensor library

int ultrasonic_trigger_pin = 9; // set the ultrasonic sensor trigger pin to 9
int ultrasonic_echo_pin = 10; // set the ultrasonic sensor echo pin to 10
int max_ultrasonic_distance_cm = 400; // set the maximum measureable distance for the ultrasonic sensor to 400cm 
NewPing sonar(ultrasonic_trigger_pin, ultrasonic_echo_pin, max_ultrasonic_distance_cm); // create a new ultrasonic sonar object based on the specified settings

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // start the serial at a baud rate of 115200
  Serial.println("Starting program...");
}

void loop() {
  // put your main code here, to run repeatedly:

  int ultrasonic_distance_cm = sonar.ping_cm(); // read the distance in cm going to the ultrasonic sensor 

  Serial.print(" Ultrasonic: ");
  Serial.print(ultrasonic_distance_cm);

  Serial.println();
}
