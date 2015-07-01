#include <Servo.h>

Servo servo[3];

typedef struct ServoWeight {
  float right; // バネの右側に位置するサーボの重み
  float left; // バネの左側に位置するサーボの重み
} ServoWeight;

// 使うサーボが１個の時の重み
ServoWeight weight[3];
// 使うサーボが2個の時の重み
ServoWeight weight2[3];

void rotateTo(Servo s, float angle) {
  s.write(angle);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servo[0].attach(2);
  servo[0].write(0);
  servo[1].attach(3);
  servo[1].write(0);
  servo[2].attach(4);
  servo[2].write(0);
}

float delayDuration = 0;
void loop() {
// 重みに応じてサーボの回転量を調整
//  servo.write(角度 * 重み); と言った具合

  delay(delayDuration);
}
