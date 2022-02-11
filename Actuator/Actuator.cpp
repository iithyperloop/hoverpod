#include "Actuator.hpp"

ActuatorException::ActuatorException(const std::string m) {
    message = "actuatorException: " + m;
}

const char * ActuatorException::what() const noexcept {
    return message.c_str();
}

Actuator::Actuator(const int p, const bool xy, const double a) {
    setPin(p);
    setIsXAngle(xy);
    setAngle(a);
}

int Actuator::getPin() {
    return pin;
}

bool Actuator::getIsXAngle() {
    return isXAngle;
}

double Actuator::getAngle() {
    const auto analogRead = [](int x) -> double { return 0.0; }; // TODO: remove this. just so it compiles.
    if (angle != analogRead(pin)) {
        throw ActuatorException("angle does not match actual angle");
    }
    return angle;
}

void Actuator::setPin(const int p) {
    if (pin < MIN_PIN || pin > MAX_PIN) {
        throw ActuatorException("invalid pin");
    }
    pin = p;
}

void Actuator::setIsXAngle(const bool xy) {
    isXAngle = xy;
}

void Actuator::setAngle(const double a) {
    if (a < MIN_ANGLE || a > MAX_ANGLE) {
        throw ActuatorException("invalid angle");
    }
    const auto analogWrite = [](int x, int z){}; // TODO: remove this. just so it compiles.
    analogWrite(pin, a);
    angle = a;
}