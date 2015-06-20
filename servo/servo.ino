#include <Servo.h> 

Servo servo[3];
void setup()
{
//	Serial.begin(9600);

	servo[0].attach(2);
	servo[0].write(180);
	servo[1].attach(3);
	servo[1].write(180);
	servo[2].attach(4);
	servo[2].write(180);
}

int i = 0;
int j = 0;
int k = 0;

int pos = 0;    // variable to store the servo position 

void loop()
{
//	while(Serial.available() < 2) {
//
//	}
//	int angle = Serial.read();
//	int index = Serial.read();
//	Serial.println(index);
//	Serial.println(angle);
//	Serial.println("---");
//	if (angle > 180) {
//		angle %= 180;
//	}
//	servo[index % 3].write(angle);

        for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
          servo[0].write(pos);              // tell servo to go to position in variable 'pos' 
          servo[2].write(pos);              // tell servo to go to position in variable 'pos' 
          delay(25);                       // waits 15ms for the servo to reach the position 
        } 
        for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
        {                                
          servo[0].write(pos);              // tell servo to go to position in variable 'pos' 
          servo[2].write(pos);              // tell servo to go to position in variable 'pos' 
          delay(25);                       // waits 15ms for the servo to reach the position 
        }
//	servo[0].write(180 + i%180);
//	servo[1].write(180 + i%180);
//	servo[2].write(180 - k * 20);    
//	i++;

	delay(15);
}
