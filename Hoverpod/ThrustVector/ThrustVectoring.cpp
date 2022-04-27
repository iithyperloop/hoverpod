#include "ThrustVectoring.h"
#include "cmath"
#include <iostream>
#include <string> 

#define PI 3.14159265359

double x_component;
double y_component;
double z_component;
double components[3];

//Thrust Vectoring Default Constructor
ThrustVectoring::ThrustVectoring() {
    setComponents(0, 0, -1);
}

ThrustVectoring::ThrustVectoring(double reading[3]) {
    newReading(reading);
}

void ThrustVectoring::setComponents(double x, double y, double z) {
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

double * ThrustVectoring::getThrustComponents() {
    return components;
}

void ThrustVectoring::newReading(double reading[3]) {
    x_component = cos((reading[0]) / 180 * PI);
    y_component = cos((reading[1]) / 180 * PI);
    z_component = - cos((reading[2]) / 180 * PI);
    setComponents(x_component, y_component, z_component);
}

