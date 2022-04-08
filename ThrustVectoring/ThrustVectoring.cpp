#include "ThrustVectoring.h"
#include "cmath"
#include <iostream>
#include <string> 

#define PI 3.14159265359

double components[3];

//Thrust Vectoring Default Constructor
ThrustVectoring::ThrustVectoring() {
    setComponents(0, 0, -1);
}

//Thrust Vectoring Non-default Constructor, given initial force vector
ThrustVectoring::ThrustVectoring(double reading[3]) {
    newReading(reading);
}

//sets the components of the thrust force vector
void ThrustVectoring::setComponents(double x, double y, double z) {
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

//returns the components of the thrust force vector
double * ThrustVectoring::getThrustComponents() {
    return components;
}

//reading takes a parameter that is an array, with the direction components of the thrust force vector
void ThrustVectoring::newReading(double reading[3]) {
    double x_component = cos((reading[0]) / 180 * PI);
    double y_component = cos((reading[1]) / 180 * PI);
    double z_component = - cos((reading[2]) / 180 * PI);
    setComponents(x_component, y_component, z_component);
}

