// Alek Popovic
// Last Updated: 11/22/2021

// What path should I include for Arduino analogRead and analogWrite?
#include <iostream>
using namespace std;

class ActuatorException : public exception {

    private:
        string message;
    
    public:

        ActuatorException(string m) {
            message = "actuatorException: " + m;
        }

        // This getter might not be necessary.
        string getMessage() {
            return message;
        }

};

class Actuator {

    private:

        // Should there be instance variables for xAngle and yAngle if we are just reading and writing data from the pin?
        // Should there be an xAngle and yAngle, or only one angle with an isXAngle boolean?
        int pin;
        bool isXAngle;
        double angle;
    
    public:

        // I don't know what the constants should actually be. We can discuss it together.
        // I set them for now, but can change later.
        const int MIN_PIN = 0;
        const int MAX_PIN = 5;
        const double MIN_ANGLE = -180;
        const double MAX_ANGLE = 180;

        Actuator(int p, bool xy, double a) {
            setPin(p);
            setIsXAngle(xy);
            setAngle(a);
        }

        int getPin() {
            return pin;
        }

        bool getIsXAngle() {
            return isXAngle;
        }

        double getAngle() {
            if (angle == analogRead(pin)) {
                return angle;
            } else {
                throw ActuatorException("angle does not match actual angle");
            }
            
        }

        void setPin(int p) {
            if (pin >= MIN_PIN && pin <= MAX_PIN) {
                pin = p;
            } else {
                throw ActuatorException("invalid pin");
            }
        }

        // This setter probably isn't necessary. It doesn't check any constraints.
        void setIsXAngle(bool xy) {
            isXAngle = xy;
        }

        void setAngle(double a) {
            if (a <= MIN_ANGLE && a >= MAX_ANGLE) {
                analogWrite(pin, a);
                angle = a;
            } else {
                throw ActuatorException("invalid angle");
            }
        }

};