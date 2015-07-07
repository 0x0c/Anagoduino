#include <Servo.h>

class Anago
{
public:
  Anago(int index1, int index2, int index3) {
    this.servo[0].attach(index1);
    this.servo[1].attach(index1);
    this.servo[2].attach(index1);
    this.servo[0].write(0);
    this.servo[1].write(0);
    this.servo[2].write(0);
  };
  ~Anago();
  float currentAngle = 0;
  Servo servo[3];
  
  /* data */
  void bendTo(int index, float angle, float duration) {

  }
  void rotateTo(float angle, float duration) {
    int op = 1;
    int startAngle = this.currentAngle;
    int endAngle = angle;
    if (startAngle > endAngle) {
      int tmp = startAngle;
      startAngle = endAngle;
      endAngle = startAngle;
      op = -1;
    }
    for (int i = startAngle; i < endAngle; i += op) {
      s.write(i);
    }
  }
};

Anago anago;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  anago = new Anago(2, 3, 4);
}

float delayDuration = 50;
void loop() {

  delay(delayDuration);
}
