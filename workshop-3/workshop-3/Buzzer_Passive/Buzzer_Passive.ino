// Global Variable
int notes[5] = {440, 494, 523, 587, 659};

void setup() {
  pinMode(12, OUTPUT);

  tone(12, 1000); // 1000 hz
  delay(100);
}

void loop() {
  tone(12, 440); // A4
  delay(10);

  tone(12, 494); // B4
  delay(10);

  tone(12, 523); // C4
  delay(10);

  tone(12, 587); // D4
  delay(10);

  tone(12, 659); // E4
  delay(10);

  noTone(12);
  delay(1000);

  for (int i=0; i<5; i++) {
    tone(12, notes[i]);
    delay(10);
    notes[i] = notes[i] + 100;
  }
  
  noTone(12);
  delay(1000);
}
