#include "Motor.hpp"

// by motor we mean engines
// this will take button input and turn engine on/off based on that

int buttonState = 1;
float takeOffSpeed = 10; // will change later

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

