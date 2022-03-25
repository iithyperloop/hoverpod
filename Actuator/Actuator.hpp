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
    int length;
public:
    Actuator(int length = 0);

    int GetLength();

    void SetLength(int nlength);
};