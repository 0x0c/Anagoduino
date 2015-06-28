#include <Servo.h> 

Servo servo[3];
void setup()
{
//	Serial.begin(9600);

	servo[0].attach(2);
	servo[0].write(0);
	servo[1].attach(3);
	servo[1].write(0);
	servo[2].attach(4);
	servo[2].write(0);
}

int i = 0;
int pos = 0;    // variable to store the servo position 
int flag = 0;

int delay_duration = 50;

void loop()
{
        for(pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
          servo[i].write(pos);              // tell servo to go to position in variable 'pos' 
          if (flag) {
            servo[(i + 1) % 3].write(pos);              // tell servo to go to position in variable 'pos' 
          }
          delay(delay_duration);                       // waits 15ms for the servo to reach the position 
        }
        for(pos = 90; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
        {                                
          servo[i].write(pos);              // tell servo to go to position in variable 'pos' 
          if (flag) {
            servo[(i + 1) % 3].write(pos);              // tell servo to go to position in variable 'pos' 
          }
          delay(delay_duration);                       // waits 15ms for the servo to reach the position 
        }
        if (flag == 1) {
          i = (i + 1) % 3;
          flag = 0;
        }
        else {
          flag = 1;
        }
	delay(50);
}
