// define all the pins that are going to be used
int joystick_x_pin = A1; // set the joystick pin for the x direction to A1
int joystick_y_pin = A2; // set the joystick pin for the y direction to A2
int joystick_btn_pin = 7; // set the joystick pin for the button direction to 7

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // start the serial at a baud rate of 115200
  Serial.println("Starting program...");

  pinMode(joystick_x_pin, INPUT); // configure the joystick pin for the x direction for input
  pinMode(joystick_y_pin, INPUT); // configure the joystick pin for the y direction for input
  pinMode(joystick_btn_pin, INPUT_PULLUP); // configure the joystick button pin for input pullup (makes button values more stable)
}

void loop() {
  // put your main code here, to run repeatedly:

  int joystick_x_value = analogRead(joystick_x_pin); // read the analog value going into the joystick pin for the x direction
  int joystick_y_value = analogRead(joystick_y_pin); // read the analog value going into the joystick pin for the y direction
  int joystick_sw_value = digitalRead(joystick_btn_pin); // read the digital value going into the joystick button pin

  // print the potentiometer values to the serial
  Serial.print(" Joystick: ");
  Serial.print(joystick_x_value);
  Serial.print(", ");
  Serial.print(joystick_y_value);
  Serial.print(", ");
  Serial.print(joystick_btn_pin);

  Serial.println();
}
