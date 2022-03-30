#include "ThrustVector.hpp"

ThrustVector::ThrustVector(float initial_tilt) : tilt(initial_tilt) {}

float ThrustVector::GetTilt() {
    return tilt;
}

void ThrustVector::SetTilt(float ntilt) {
    tilt = ntilt;
}