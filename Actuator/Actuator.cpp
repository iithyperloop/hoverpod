#include "Actuator.hpp"

Actuator::Actuator(const int length) : length(length) {}

int Actuator::GetLength() const {
    return length;
}

void Actuator::SetLength(const int nlength) {
    length = nlength;
}