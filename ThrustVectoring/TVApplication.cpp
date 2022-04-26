#include <iostream>
#include "ThrustVectoring.cpp"
#include "ThrustVectoring.h"
#define PI 3.14159265359

using namespace std;

int main() {

    ThrustVectoring tv;

    for (int i = 0; i < 3; i++) {
        cout << tv.getThrustComponents()[i] << ", ";
    }

    double r[] = {-90, -90, 0};
    tv.newReading(r);

    cout<< "\n";

    for (int i = 0; i < 3; i++) {
        cout << tv.getThrustComponents()[i] << ", ";
    }
}