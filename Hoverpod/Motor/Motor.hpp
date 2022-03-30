#pragma once

class Motor
{
    double speed;
public:
    Motor();

    [[nodiscard]] double getSpeed() const;

    void setSpeed(double val);

    void increaseSpeed(double val);

    void decreaseSpeed(double val);
};