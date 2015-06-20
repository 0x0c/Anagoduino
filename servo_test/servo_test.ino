void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.write(2);
  Serial.write(i * 30 % 180);
  delay(500);
  
  Serial.write(3);
  Serial.write(i * 30 % 180);
  delay(500);
  
  Serial.write(4);
  Serial.write(i * 30 % 180);
  delay(500);
  
  i++;
}
