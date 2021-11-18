#include "HeightSensor.hpp"

HeightSensor::HeightSensor(float initial_height) : height(initial_height) {}

float HeightSensor::get_height(){
    return height;
}

void HeightSensor::set_height(float new_height){
    height=new_height;
}