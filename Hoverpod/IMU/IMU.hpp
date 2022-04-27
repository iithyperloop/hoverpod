#pragma once
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include "vn/sensors.h"

using namespace std;
using namespace vn::math;

class IMU {
    using dat = vn::sensors::YawPitchRollMagneticAccelerationAndAngularRatesRegister;
    vn::sensors::VnSensor sensor;
    dat IMU_data;

    static constexpr int baudrate = 115200;
public:
    explicit IMU();

    ~IMU();

    void update();

    [[nodiscard]] vec3f get_acel_values();

    [[nodiscard]] vec3f get_gyro_values();

    [[nodiscard]] vec3f get_mag_values();

    [[nodiscard]] vec3f get_yaw_pitch_roll_values();


		mat3f rotMatrix(vec3f yawPitchRoll) {
			float yaw = yawPitchRoll[0];
			float pitch = yawPitchRoll[1];
			float roll = yawPitchRoll[2];

			float su = sin(roll);
			float cu = cos(roll);

			float sv = sin(pitch);
			float cv = cos(pitch);

			float sw = sin(yaw);
			float cw = cos(yaw);


			mat3f matrix( (cv * cw),  (su * sv * cw - cu*sw),  (su * sw + cu * sv * cw),
										(cv * sw), (cu * cv + su * sv * sw), (cu * sv * sw - su * cw),
											(-sv),          (su * cv),                (cu * cv) );

			return matrix; //returns rotation matrix
		}

		vec3f integrate(vec3f prev_acc, vec3f curr_acc, float timestep) {
			vec3f velocity;
			velocity.x = timestep * ((curr_acc.x + prev_acc.x)/2.0);
			velocity.y = timestep * ((curr_acc.y + prev_acc.y)/2.0);
			velocity.z = timestep * ((curr_acc.z + prev_acc.z)/2.0);

			return velocity;
		}

		vec3f normalize(mat3f rotationMatrix, vec3f curr_acc) {
			vec3f angleVec(0.0f, 0.0f, 1.0f); //[0, 0, 1]
			/*INVERT MATRIX*/
			float mat[3][3], i, j;
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
	         mat[i][j] = rotationMatrix(i)(j);
				 }
			 }
			float determinant = 0;
			//check if it is invertible
			for(i = 0; i < 3; i++) {
				determinant = determinant + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
			}
			if (determinant > 0) {
				for(i = 0; i < 3; i++){
					for(j = 0; j < 3; j++) {
					rotationMatrix(i)(j) = ((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3])) / determinant;
				}
			}
			//curr_acc = multiply invert matrix to angleVec
			curr_acc += rotationMatrix.0 * angleVec;
			curr_acc += rotationMatrix.1 * angleVec;
			curr_acc += rotationMatrix.2 * angleVec;

			return curr_acc;
		}
		return curr_acc;
	}

		void do_imu() {

			//variables
			vec3f velocity;
			vec3f prev_accel(0.0f, 0.0f, 0.0f);
			static vec3f sumVelocity(0.0f, 0.0f, 0.0f);

			for (;;) {
				this_thread::sleep_for(chrono::milliseconds(3));

				/*ROTATION MATRIX*/
				vec3f ypr = get_yaw_pitch_roll_values();
				mat3f rotationMatrix = rotMatrix(ypr);

				/*INTEGRATION*/
				//get curr acceleration
				vec3f curr_accel = get_acel_values();
				curr_accel = normalize(rotationMatrix, curr_accel);
				//sumVelocity += integrate()
				sumVelocity += integrate(prev_accel, curr_accel, 0.0025); //time value undecided
				//prev acceleration = current acceleration
				cout << "instantenous velocity: " << sumVelocity << endl;
				prev_accel = curr_accel;


				printf("Velocity: (%f %f %f)\n", velocity.x, velocity.y, velocity.z);
			}
		}
}; 
