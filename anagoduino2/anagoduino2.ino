#include <vector>
#include <Servo.h>

namespace Anagoduino
{
	using namespace std;
	class Anago
	{
	public:
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
		};
		~Anago();

		/* data */
		float current_angle;
		Servo servo[3];
		int servo_angle[3];

		/* function */
		void bend(int indexs[], int angles[], float duration) {
			int start_angle1 = this->servo_angle[indexs[0]];
			int start_angle2 = this->servo_angle[indexs[1]];
			int end_angle = max(angles[0], angles[1]);
			float step = end_angle / duration;
			float wait = duration / step;
			for (int i = start_angle1, j = start_angle2; i < end_angle, j < end_angle; i += step, j += step) {
				this->bend(indexs[0], i, wait);
				this->bend(indexs[1], j, wait);
			}
		}

		void bend(int index, int angle, float duration) {
			int op = 1;
			int i = 0;
			int start_angle = this->servo_angle[index];
			int end_angle = angle;
			if (start_angle > end_angle) {
				int tmp = start_angle;
				start_angle = end_angle;
				end_angle = start_angle;
				op = -1;
			}

			float wait = duration / angle;
			for (int i = start_angle; i < end_angle; i += op) {
		  		this->servo[index].write(i);
		  		delay(wait);
			}
			
			this->servo_angle[index] = end_angle;
		}

		void rotate(float angle, float duration) {
			// int op = 1;
			// int start_angle = this.current_angle;
			// int end_angle = angle;
			// if (start_angle > end_angle) {
			// 	int tmp = start_angle;
			// 	start_angle = end_angle;
			// 	end_angle = start_angle;
			// 	op = -1;
			// }
			// for (int i = start_angle; i < end_angle; i += op) {
		 //  		s.write(i);
			// }
		}
	};	
}

using namespace std;
using namespace Anagoduino;

#define size_of_array(array) array + (sizeof(array)/sizeof(int))

Anago *anago;
void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	anago = new Anago(2, 3, 4);
}

int global_angle = 0;
float duration = 1000;
float loop_wait_interval = 1000;
void loop() {
	int idx[] = {0, 1};
	int ang[] = {global_angle, global_angle};
	anago->bend(idx, ang, duration);
	delay(loop_wait_interval);
	global_angle += 30;
	global_angle %= 180;
}
