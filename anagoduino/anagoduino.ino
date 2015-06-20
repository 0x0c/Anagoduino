void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float delayDuration = 0;
  if (analogRead(A0) > 500) {
    Serial.println("yeah");
    delayDuration = 100;
  }
  
  int s = 650;
  int x = analogRead(A3) - s;
  int y = analogRead(A4) - s;
  int z = analogRead(A5) - s;
  int n = sqrt(x*x + y*y + z*z);
  if (n > 150) {
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);
    Serial.println("w");
    delayDuration = 100;
  }
  
  delay(delayDuration);
}
