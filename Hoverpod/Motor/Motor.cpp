#include "Motor.hpp"

Motor::Motor() : speed(0) {}

double Motor::getSpeed() const {
    return speed;
}

void Motor::setSpeed(const double val) {
    speed = val > 0 ? val : 0;
}

void Motor::increaseSpeed(double val) {
    setSpeed(getSpeed() + val);
}

void Motor::decreaseSpeed(double val) {
    setSpeed(getSpeed() - val);
}