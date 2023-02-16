void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  pinMode(7, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Setup Complete.");
}

// TODO: EXPLAIN THIS LATER
int led_brightness = 0

void loop() {
  // put your main code here, to run repeatedly:  
  int button = digitalRead(7);

  if (button == LOW) {
    led_brightness += 1;
  }
  else {
    led_brightness -= 1;
  }
  analogWrite(13, led_brightness);
}
