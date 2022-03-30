

// This code is designed for the TMP36 temperature sensor for arduino

#include "TempSensor.hpp"

TempSensor::TempSensor(float initial_temp) : temp(initial_temp) {}

float TempSensor::get_temp()
{
	return temp;
}

void TempSensor::set_temp(float new_temp)
{
	temp = new_temp;
}
