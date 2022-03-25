#pragma once

class Motor
{
    double speed;
public:
    Motor();

    double getSpeed() const;

    void setSpeed(double val);
};