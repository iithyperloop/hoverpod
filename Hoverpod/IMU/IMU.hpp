#pragma once
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include "vn/sensors.h"

class IMU {
    using dat = vn::sensors::YawPitchRollMagneticAccelerationAndAngularRatesRegister;
    vn::sensors::VnSensor sensor;
    dat IMU_data;

    static constexpr int baudrate = 115200;
public:
    explicit IMU();

    ~IMU();

    void update();

    [[nodiscard]] vn::math::vec3f get_acel_values();

    [[nodiscard]] vn::math::vec3f get_gyro_values();

    [[nodiscard]] vn::math::vec3f get_mag_values();

    [[nodiscard]] vn::math::vec3f get_yaw_pitch_roll_values();

	float integrate_DOUBLY(float var2, float var1, float time_step) {
		return (var2 - var1) / time_step;
	}

	void do_imu() {
		vn::math::vec3f velocity;
		auto old_accel = get_acel_values();
		for (;;) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			auto new_accel = get_acel_values();
			velocity.x = integrate_DOUBLY(old_accel.x, new_accel.x, 50000);
			velocity.y = integrate_DOUBLY(old_accel.y, new_accel.y, 50000);
			velocity.z = integrate_DOUBLY(old_accel.z, new_accel.z, 50000);
			old_accel = get_acel_values();
			printf("Velocity: (%f %f %f)\n", velocity.x, velocity.y, velocity.z);
		}
	}
};
