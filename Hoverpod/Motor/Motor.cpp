#include "Motor.hpp"
#include <iostream>

// by motor we mean engines
// this will take button input and turn engine on/off based on that


Motor::Motor() {
    int buttonState = 1;
    const float takeOffSpeed = 10; // will change value once tested
    float speed;
}

double Motor::getSpeed() {
    return speed;
}

void Motor::setSpeed(double val) {
    speed = val > 0 ? val : 0; //making sure that speed is pos val
}

void Motor::increaseSpeed(double val) {
    setSpeed(getSpeed() + val);
}

void Motor::decreaseSpeed(double val) {
    setSpeed(getSpeed() - val);
}

int Motor::getButtonState() {
    return buttonState;
}

void Motor::setButtonState(int val) {
    buttonState = val;
}

void Motor::turnMotorOn() {
    
// Input from button goes 1-0 then we turn on
    if (getButtonState() == 1) {
        if (getButtonState() == 0) {
            if (getSpeed() == 0) {
                for (int i = 0; i < takeOffSpeed(); i++) {
                    increaseSpeed(i);
                }
            }
            else {
                int currentSpeed = getSpeed();
                for (int j = 0; j < currentSpeed; j++) {
                    decreaseSpeed(j);
                }
            }
            
        }
    }

}
