#include <iostream>
#include "HeightSensor.hpp"

int run_hs_test() {
    HeightSensor height_sensor(99.0f);
    std::cout << "intial height: " << height_sensor.get_height() << std::endl;
    height_sensor.set_height(123123.0f);
    std::cout << "new height: " << height_sensor.get_height() << std::endl;
}