#include "Actuator.hpp"

ActuatorException::ActuatorException(const char* m) {
    message = "actuatorException: " + std::string(m);
}

const char *ActuatorException::what() const noexcept {
    return message.c_str();
}

Actuator::Actuator(const int length) : length(length) {}

int Actuator::GetLength() {
    return length;
}

void Actuator::SetLength(const int nlength) {
    length = nlength;
}