#include "IMU.hpp"


IMU::IMU() : IMU_data({}) {
#ifdef _WIN32
	sensor.connect("COM6", baudrate);
#elif __linux__
	sensor.connect("/dev/ttyUSB0", baudrate);
#elif __APPLE__
	sensor.connect("/dev/tty.usbserial-FT3JX4GV", baudrate);
#endif
	update();
}

IMU::~IMU()
{
	sensor.disconnect();
}

void IMU::update()
{
	IMU_data = sensor.readYawPitchRollMagneticAccelerationAndAngularRates();
}

vn::math::vec3f IMU::get_acel_values()
{
	update();
	return IMU_data.accel;
}

vn::math::vec3f IMU::get_gyro_values()
{
	update();
	return IMU_data.gyro;
}

vn::math::vec3f IMU::get_mag_values()
{
	update();
	return IMU_data.mag;
}

vn::math::vec3f IMU::get_yaw_pitch_roll_values()
{
	update();
	return IMU_data.yawPitchRoll;
}