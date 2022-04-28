// Alek Popovic
// Last Updated: 1/14/2022
#pragma once

enum class ActuatorStatus
{
    STATUS_OK,
    STATUS_LENGTH_ERROR
};

class Actuator {
    int length;
    float joystickOutput[];
    
public:
    Actuator(int length = 0);

    [[nodiscard]] int GetLength() const;

    void SetLength(int nlength);
};
