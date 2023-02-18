// define all the pins that are going to be used
int pot_pin = A0; // set the potentiometer signal pin to A0

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); // start the serial at a baud rate of 115200
  Serial.println("Starting program...");

  pinMode(pot_pin, INPUT); // configure the potentiometer pin for input
}

void loop() {
  // put your main code here, to run repeatedly:

  int pot_value = analogRead(pot_pin); // read the analog value going into the potentiometer pin
  int mapped_pot_value = map(pot_value, 0, 1023, 0, 255); // rescale the potentiometer value from 0 - 1023 down to 0 - 255

  // print the potentiometer values to the serial
  Serial.print("Pot: ");
  Serial.print(pot_value);
  Serial.print(", ");
  Serial.print(mapped_pot_value);

  Serial.println();
}
