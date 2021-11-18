#include "IMU.hpp"

IMU::IMU(acceleration_data val) : acel_values(std::move(val)) {}

IMU::IMU() {
    read_sensor_data();
}

std::vector<float> IMU::read_sensor_data() {
    // read data from sensor.. how!?
    acel_values = {
        .x = 0,
        .y = 0,
        .z = 0
    };
    return {};
}

IMU::acceleration_data IMU::get_acel_values() { 
    return acel_values; 
}

float IMU::get_x_acel_value() {
    return get_acel_values().x;
}

float IMU::get_y_acel_value() {
    return get_acel_values().y;
}

float IMU::get_z_acel_value() {
    return get_acel_values().z;
}

void IMU::set_acel_values(acceleration_data val) {
    acel_values = std::move(val);
}

void IMU::set_x_acel_value(float val) {
    acel_values.x = val;
}

void IMU::set_y_acel_value(float val) {
    acel_values.y = val;
}

void IMU::set_z_acel_value(float val) {
    acel_values.y = val;
}