#pragma once
class ThrustVector {
    float tilt;
public:
    ThrustVector(float initial_tilt = 0);

    float GetTilt();

    void SetTilt(float ntilt);
};