void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  Serial.begin(9600);
  Serial.println("Setup Complete.");
}

// TODO: EXPLAIN THIS LATER
//int led_brightness = 0

void loop() {
  // put your main code here, to run repeatedly:  

// COMMENT THIS OUT AND IMPLEMENT ABOVE
//  int led_brightness = 0
  
  // Make LED brighter
  for (int i = 0; i < 255; i += 1) {
    analogWrite(13, led_brightness);
    delay(50);
    led_brightness += 1;
  }

  // Make LED dimmer
  for (int i = 0; i < 255; i += 1) {
    analogWrite(13, led_brightness);
    delay(50);
    led_brightness -= 1;
  }
}
