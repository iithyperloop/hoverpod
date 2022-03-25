// Alek Popovic
// Last Updated: 1/14/2022
#pragma once
#include <string>

class ActuatorException : public std::exception {
protected:
    std::string message;
public:
    explicit ActuatorException(const char* m);

    [[nodiscard]] const char *what() const noexcept override;
};

class Actuator {
    // Should there be instance variables for xAngle and yAngle if we are just reading and writing data from the pin?
    // Should there be an xAngle and yAngle, or only one angle with an isXAngle boolean?
    int pin;
    bool isXAngle;
    double angle;

    // I don't know what the constants should actually be. We can discuss it together.
    // I set them for now, but can change later.
    static constexpr int MIN_PIN = 0;
    static constexpr int MAX_PIN = 5;
    static constexpr double MIN_ANGLE = -180;
    static constexpr double MAX_ANGLE = 180;
public:
    Actuator(int p, bool xy, double a);

    [[nodiscard]] int getPin() const;

    [[nodiscard]] bool getIsXAngle() const;

    [[nodiscard]] double getAngle() const;

    void setPin(int p);

    // This setter probably isn't necessary. It doesn't check any constraints.
    void setIsXAngle(bool xy);

    void setAngle(double a);

    void turn_on();

    void turn_off();
};