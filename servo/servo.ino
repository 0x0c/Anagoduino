#include <Servo.h> 

int servo_count = 3;
Servo servo[3];
void setup()
{
	Serial.begin(9600);

	servo[0].attach(2);
	servo[0].write(0);
	servo[1].attach(4);
	servo[1].write(0);
	servo[2].attach(3);
	servo[2].write(0);
  delay(2000);
}

int i = 0;
int pos = 0;    // variable to store the servo position 
int flag = 0;

int delay_duration = 70;

bool stop_servo = 0;
void loop()
{
  if (Serial.available() > 0) {
    Serial.read();
    stop_servo = !stop_servo;
  }
  if (stop_servo) return;
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo[i].write(pos);              // tell servo to go to position in variable 'pos' 
    if (flag) {
      servo[(i + 1) % servo_count].write(pos);              // tell servo to go to position in variable 'pos' 
    }
    delay(delay_duration);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo[i].write(pos);              // tell servo to go to position in variable 'pos' 
    if (flag) {
      servo[(i + 1) % servo_count].write(pos);              // tell servo to go to position in variable 'pos' 
    }
    delay(delay_duration);                       // waits 15ms for the servo to reach the position 
  }
  if (flag == 1) {
    i = (i + 1) % servo_count;
    flag = 0;
  }
  else {
    flag = 1;
  }
 delay(50);
}
