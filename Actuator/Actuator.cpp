#include "Actuator.hpp"

ActuatorException::ActuatorException(const char* m) {
    message = "actuatorException: " + std::string(m);
}

const char *ActuatorException::what() const noexcept {
    return message.c_str();
}

Actuator::Actuator(const int p, const bool xy, const double a) : pin(p), isXAngle(xy), angle(a) {
    setPin(p);
    setIsXAngle(xy);
    setAngle(a);
}

int Actuator::getPin() const {
    return pin;
}

bool Actuator::getIsXAngle() const {
    return isXAngle;
}

double Actuator::getAngle() const {
    constexpr auto analogRead = [](int x) -> double { return 0.0; }; // TODO: remove this. just so it compiles.
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
    constexpr auto analogWrite = [](int x, double z) {}; // TODO: remove this. just so it compiles.
    analogWrite(pin, a);
    angle = a;
}

void Actuator::turn_on() {
    // TODO: what the HECK do i do here lol
}

void Actuator::turn_off() {
    // TODO: what the HECK do i do here lol
}