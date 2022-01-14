#include "Motor.hpp"

double Motor::getSpeed() {
    return speed;
}

void Motor::setSpeed(double val) {
    speed = val > 0 ? val : 0;
}