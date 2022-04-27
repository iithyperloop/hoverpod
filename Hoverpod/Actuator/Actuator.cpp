#include "Actuator.hpp"
#include <iostream>

use namespace std;

int main() {

	// input from Joystick [0,1023] for x,y,z
	float joystickOutput[3] = {};

	// sub 512 from it so that it makes more sense logically in terms of coordinate system
	float x_in = joystickOutput[0];
	float y_in = joystickOutput[1];
	float z_in = joystickOutput[2];

	/*
	* Directional Logic:
	*
	* + means extended
	* - means retracted
	*
	* - Forward:  1-, 2-, 3-, 4+, 5-, 6-, 7-, 8+
	* - Backward: 1+, 2+, 3+, 4-, 5+, 6+, 7+, 8-
	* - Right:    1-, 2+, 3+, 4+, 5-, 6+, 7+, 8+
	* - Left:     1+, 2-, 3-, 4-, 5+, 6-, 7-, 8-
	* - CCW:      1+, --, 3-, --, 5-, --, 7+, --
	* - CW:       1-, --, 3+, --, 5+, --, 7-, --
	*
	*
	* top axis actuator range: 4.875mm in each direction
	* bottom axis actuator range: 4.188mm in each direction
	*
	*/

	float act1 = 0;
	float act2 = 0;
	float act3 = 0;
	float act4 = 0;
	float act5 = 0;
	float act6 = 0;
	float act7 = 0;
	float act8 = 0;

	float topMax = 4.875;
	float topMin = -4.875;
	float bottomMax = 4.188;
	float bottomMin = -4.188;


	switch (x_in, y_in, z_in) {
	case (x_in == 0 && y_in > 0 && y_in < 1023 && z_in > 0 && z_in < 1023):
		// Move Left:     1+, 2-, 3-, 4-, 5+, 6-, 7-, 8-
		act1 = topMax;
		act2 = bottomMin;
		act3 = topMin;
		act4 = bottomMin;
		act5 = topMax;
		act6 = bottomMin;
		act7 = topMin;
		act8 = bottomMin;
		break; //optional
	case (x_in == 1023 && y_in > 0 && y_in < 1023 && z_in > 0 && z_in < 1023):
		// Move Right:    1-, 2+, 3+, 4+, 5-, 6+, 7+, 8+
		act1 = topMin;
		act2 = bottomMax;
		act3 = topMax;
		act4 = bottomMax;
		act5 = topMin;
		act6 = bottomMax;
		act7 = topMax;
		act8 = bottomMax;
		break; //optional
	case (x_in > 0 && x_in < 1023 && y_in == 0 && z_in > 0 && z_in < 1023):
		// Move Backward: 1+, 2+, 3+, 4-, 5+, 6+, 7+, 8-
		act1 = topMax;
		act2 = bottomMax;
		act3 = topMax;
		act4 = bottomMin;
		act5 = topMax;
		act6 = bottomMax;
		act7 = topMax;
		act8 = bottomMin;
		break; //optional
	case (x_in > 0 && x_in < 1023 && y_in == 1023 && z_in > 0 && z_in < 1023):
		// Move Forward:  1-, 2-, 3+, 4-, 5+, 6+, 7-, 8+
		act1 = topMin;
		act2 = bottomMin;
		act3 = topMax;
		act4 = bottomMin;
		act5 = topMax;
		act6 = bottomMax;
		act7 = topMin;
		act8 = bottomMax;
		break;
	case (x_in > 0 && x_in < 1023 && y_in > 0 && y_in < 1023 && z_in == 0):
		// Turn CCW:      1+, --, 3-, --, 5-, --, 7+, --
		act1 = topMax;
		act2 = 0;
		act3 = topMin;
		act4 = 0;
		act5 = topMin;
		act6 = 0;
		act7 = topMax;
		act8 = 0;
		break;
	case (x_in > 0 && x_in < 1023 && y_in > 0 && y_in < 1023 && z_in == 1023):
		// Turn CW:       1-, --, 3+, --, 5+, --, 7-, --
		act1 = topMin;
		act2 = 0;
		act3 = topMax;
		act4 = 0;
		act5 = topMax;
		act6 = 0;
		act7 = topMin;
		act8 = 0;
		break;	 
	default:
		// Return all actuators/engines to centered
		// Don't move
		act1 = 0;
		act2 = 0;
		act3 = 0;
		act4 = 0;
		act5 = 0;
		act6 = 0;
		act7 = 0;
		act8 = 0;
	}
}
