#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>
#include <Servo.h>

namespace Anagoduino
{
	class Anago
	{
	public:
		#define number_of_servo 3
		Anago(int index1, int index2, int index3) {
			this->servo[0].attach(index1);
			this->servo[1].attach(index2);
			this->servo[2].attach(index3);

			this->servo[0].write(0);
			this->servo[1].write(0);
			this->servo[2].write(0);

			this->servo_angle[0] = 0;
			this->servo_angle[1] = 0;
			this->servo_angle[2] = 0;
			this->current_angle = 0;
			this->current_rotation = 0;

			this->weight[0].forward_by_back = 1;
			this->weight[1].forward_by_back = 1;
			this->weight[2].forward_by_back = 1;
		};
		~Anago();

		/* data */
		float current_angle;
		float current_rotation;
		Servo servo[3];
		int servo_angle[3];
		typedef struct ServoWeight {
			double forward_by_back;//前方のservo[(i + 1) % number_of_servo] を後方のservo[i] に対してどの強さで引くか
		} ServoWeight;
		// 使うサーボが1個の時の重み
		ServoWeight weight[3];

		/* function */
		void bend(int angle, float duration) {

		}

		void bend(int indexs[], int angles[], float duration) {
			int start_angle1 = this->servo_angle[indexs[0]];
			int start_angle2 = this->servo_angle[indexs[1]];
			int end_angle1 = angles[0];
			int end_angle2 = angles[1];
			float step1 = angles[0] / duration;
			float step2 = angles[2] / duration;

			float wait = duration / max(fabs(start_angle1 - end_angle1) / step1, fabs(start_angle2 - end_angle2) / step2);
			for (float i = start_angle1, j = start_angle2; i < end_angle1 && j < end_angle2; i += step1, j += step2) {
				if(i <  end_angle1) {
					this->bend(indexs[0], i);
				}
				if(j < end_angle2) {
					this->bend(indexs[1], j);
				}
				delay(wait);
			}
		}

		void bend(int index, int angle, float duration) {
			int idx[] = {index, 0};
			int ang[] = {angle, this->servo_angle[0]};
			this->bend(idx, ang, duration);
		}

		void bend(int index, int angle) {
			int op = 1;
			int i = 0;
			int start_angle = this->servo_angle[index];
			int end_angle = angle;
			if (start_angle > end_angle) {
				// std::swap(start_angle, end_angle);
				op = -1;
			}
			Serial.print(start_angle);
			Serial.print("~");
			Serial.println(end_angle);
			for (int i = start_angle; i != end_angle; i += op) {
				this->servo[index].write(i);
				Serial.println(i);
			}
			
			this->servo_angle[index] = end_angle;
		}

		void rotate(float angle) {//, float duration) {
			int i = angle / 120;
			int stan = 0; //servo number whose pos is not adjusted
			int change = 1; //servo number whose pos is adjusted
			double change_deg_weight = 0.0; //deg-based-weight to adjust pos of changing servo
			double change_servo_weight = 1.0; //servo-based-weight to adjust pos of changing servo
			double deg_rad = (double)(angle - 120 * i) * PI / 180.0;//;
			if (deg_rad < PI / 3.0){
				stan = i; 
				change = (i + 1) % number_of_servo;
				change_deg_weight = sin(deg_rad) / sin(2 * PI / 3.0 - deg_rad);
				change_servo_weight = this->weight[i].forward_by_back;
			}
			else {
				stan = (i + 1) % number_of_servo;
				change = i;
				change_deg_weight = sin(2 * PI / 3.0 - deg_rad) / sin(deg_rad);
				change_servo_weight = 1.0 / this->weight[i].forward_by_back;
			}

			// ここから一時的なコード
			int delay_duration = 50;
			for(int pos = 0; pos <= 180; pos += 30){
				//adjust pos by degree
				//when you use servo_weight, write like this
				double tempos = (double)pos;
				if(change_servo_weight > 1.0) {
					tempos = tempos / change_servo_weight;
				}
				this->servo[change].write((int) tempos * change_deg_weight * change_servo_weight);
				//servo[change].write(int(pos * change_deg_weight));
				this->servo[stan].write(pos);
				delay(delay_duration);
			}
			for(int pos = 180; pos >= 0; pos -= 30) {
    //adjust pos by degree
    //when you use servo_weight, write like this
	    		double tempos = (double)pos;
				if(change_servo_weight > 1.0) {
					tempos = tempos / change_servo_weight;
				}
				this->servo[change].write((int) tempos * change_deg_weight * change_servo_weight);
				//servo[change].write(int(pos * change_deg_weight));
				this->servo[stan].write(pos);
				delay(delay_duration);
			}
		}
	};	
}

using namespace std;
using namespace Anagoduino;

Anago *anago;
void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	anago = new Anago(2, 3, 4);
	anago->bend(0, 0);
	anago->bend(1, 0);
	anago->bend(2, 0);
}

float duration = 1000;
float loop_wait_interval = 50;
void loop() {
	if (Serial.available() > 0){
		int angle = Serial.read() * 2;
		anago->rotate(angle);
		// anago->bend(0, angle);
		Serial.println(angle);
		// anago->bend(0, angle);
		// int idx[] = {0, 1};
		// int ang[] = {angle, angle};
		// anago->bend(idx, ang, duration);
		delay(loop_wait_interval);
	}
}
