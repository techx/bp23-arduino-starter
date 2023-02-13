void setup()
{
  pinMode(12,OUTPUT);
}
void loop()
{
  // Making a "ticking" sound like a clock
  digitalWrite(12,HIGH);
  delay(1);//wait for 1ms
  digitalWrite(12,LOW);
  delay(500);//wait for 1ms
} 
