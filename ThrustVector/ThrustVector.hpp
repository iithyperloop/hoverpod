#pragma once

enum class ThrustVectorStatus
{
	STATUS_OK,
    STATUS_TILT_TOO_LARGE,
    STATUS_TILT_TOO_SMALL
};

class ThrustVector {
    float tilt;
public:
    ThrustVector(float initial_tilt = 0);

    float GetTilt();

    void SetTilt(float ntilt);
};