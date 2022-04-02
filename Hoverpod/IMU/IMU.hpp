#pragma once
#include <vector>
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
};