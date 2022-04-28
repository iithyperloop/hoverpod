#include "Actuator.hpp"
/*
* 
* Linear actuators are connected to linear actuator controller.
* On controller:
* - FWD wire (green)
* --- If set the pin to HIGH with arduino, then actuator extends
* - REV wire (blue)
* --- If set the pin to HIGH with arduino, then actuator retract
* 
* Out of both of these pins, one should be set to HIGH and one to LOW. 
* If both are set to HIGH or both are set to LOW, it will not run.
* 
* 
*/

Actuator::Actuator(int length) {

	// sub 512 from it so that it makes more sense logically in terms of coordinate system
	float x_in = joystickOutput[0];
	float y_in = joystickOutput[1];
	float z_in = joystickOutput[2];

	float x_scale[2];
	float y_scale[2];
	float z_scale[2];

	float x_scaleL;
	float x_scaleR;
	float y_scaleF;
	float y_scaleB;
	float z_scaleCW;
	float z_scaleCCW;

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

	const float topMax = 4.875;
	const float topMin = -4.875;
	const float bottomMax = 4.188;
	const float bottomMin = -4.188;

}

//Getters

float Actuator::getX() {
	return x_in;
}

float Actuator::getY() {
	return y_in;
}

float Actuator::getZ() {
	return z_in;
}

std::tuple<float, float> Actuator::getX_Scale() {
	return std::make_tuple(x_scaleL, x_scaleR);
}

std::tuple<float, float> Actuator::getY_Scale() {
	return std::make_tuple(y_scaleB, y_scaleF);
}

std::tuple<float, float> Actuator::getZ_Scale() {
	return std::make_tuple(z_scaleCCW, z_scaleCW);
}

float Actuator::getAct1() {
	return act1;
}

float Actuator::getAct2() {
	return act2;
}

float Actuator::getAct3() {
	return act3;
}

float Actuator::getAct4() {
	return act4;
}

float Actuator::getAct5() {
	return act5;
}

float Actuator::getAct6() {
	return act6;
}

float Actuator::getAct7() {
	return act7;
}

float Actuator::getAct8() {
	return act8;
}


//Setters
void Actuator::setX(float joystickOutput[]) {
	x_in = joystickOutput[0];
}

void Actuator::setY(float joystickOutput[]) {
	y_in = joystickOutput[1];
}

void Actuator::setZ(float joystickOutput[]) {
	z_in = joystickOutput[2];
}

void Actuator::setX_Scale(float x_in) {
	if (x_in < (1023.0 / 2.0)) {
		x_scaleL = x_in / 512.0;
		x_scaleR = 0.0;
	}
	else if (x_in > (1023.0 / 2.0)) {
		x_scaleL = 0.0;
		x_scaleR = (x_in - 512.0) / 512.0;
	}
	else {
		x_scaleL = 0.0;
		x_scaleR = 0.0;
	}
}

void Actuator::setY_Scale(float y_in) {
	if (y_in < (1023.0 / 2.0)) {
		y_scaleB = y_in / 512.0;
		y_scaleF = 0.0;
	}
	else if (y_in > (1023.0 / 2.0)) {
		y_scaleB = 0.0;
		y_scaleF = (y_in - 512.0) / 512.0;
	}
	else {
		y_scaleB = 0.0;
		y_scaleF = 0.0;
	}
}

void Actuator::setZ_Scale(float z_in) {
	if (z_in < (1023.0 / 2.0)) {
		z_scaleCCW = z_in / 512.0;
		z_scaleCW = 0.0;
	}
	else if (z_in > (1023.0 / 2.0)) {
		z_scaleCCW = 0.0;
		z_scaleCW = (z_in - 512.0) / 512.0;
	}
	else {
		z_scaleCCW = 0.0;
		z_scaleCW = 0.0;
	}
}


void Actuator::setAct1(float val) {
	if (val > topMax) {
		act1 = topMax;
	}
	else if (val < topMin) {
		act1 = topMin;
	}
	else {
		act1 = val;
	}
}

void Actuator::setAct2(float val) {
	if (val > bottomMax) {
		act2 = bottomMax;
	}
	else if (val < bottomMin) {
		act2 = bottomMin;
	}
	else {
		act2 = val;
	}
}

void Actuator::setAct3(float val) {
	if (val > topMax) {
		act3 = topMax;
	}
	else if (val < topMin) {
		act3 = topMin;
	}
	else {
		act3 = val;
	}
}

void Actuator::setAct4(float val) {
	if (val > bottomMax) {
		act4 = bottomMax;
	}
	else if (val < bottomMin) {
		act4 = bottomMin;
	}
	else {
		act4 = val;
	}
}

void Actuator::setAct5(float val) {
	if (val > topMax) {
		act5 = topMax;
	}
	else if (val < topMin) {
		act5 = topMin;
	}
	else {
		act5 = val;
	}
}

void Actuator::setAct6(float val) {
	if (val > bottomMax) {
		act6 = bottomMax;
	}
	else if (val < bottomMin) {
		act6 = bottomMin;
	}
	else {
		act6 = val;
	}
}

void Actuator::setAct7(float val) {
	if (val > topMax) {
		act7 = topMax;
	}
	else if (val < topMin) {
		act7 = topMin;
	}
	else {
		act7 = val;
	}
}

void Actuator::setAct8(float val) {
	if (val > bottomMax) {
		act8 = bottomMax;
	}
	else if (val < bottomMin) {
		act8 = bottomMin;
	}
	else {
		act8 = val;
	}
}


// Movement Methods (not sure what output should be since idk how to get the data to the actuators)
void Actuator::moveForward() {
	// Move Forward:  1-, 2-, 3+, 4-, 5+, 6+, 7-, 8+
	float tempAct1 = std::get<1>(getY_Scale()) * topMin;
	float tempAct2 = std::get<1>(getY_Scale()) * bottomMin;
	float tempAct3 = std::get<1>(getY_Scale()) * topMax;
	float tempAct4 = std::get<1>(getY_Scale()) * bottomMin;
	float tempAct5 = std::get<1>(getY_Scale()) * topMax;
	float tempAct6 = std::get<1>(getY_Scale()) * bottomMax;
	float tempAct7 = std::get<1>(getY_Scale()) * topMin;
	float tempAct8 = std::get<1>(getY_Scale()) * bottomMax;
	
	setAct1(tempAct1);
	setAct2(tempAct2);
	setAct3(tempAct3);
	setAct4(tempAct4);
	setAct5(tempAct5);
	setAct6(tempAct6);
	setAct7(tempAct7);
	setAct8(tempAct8);

}

void Actuator::moveBackward() {
	// Move Backward: 1+, 2+, 3+, 4-, 5+, 6+, 7+, 8-
	float tempAct1 = std::get<0>(getY_Scale()) * topMax;
	float tempAct2 = std::get<0>(getY_Scale()) * bottomMax;
	float tempAct3 = std::get<0>(getY_Scale()) * topMax;
	float tempAct4 = std::get<0>(getY_Scale()) * bottomMin;
	float tempAct5 = std::get<0>(getY_Scale()) * topMax;
	float tempAct6 = std::get<0>(getY_Scale()) * bottomMax;
	float tempAct7 = std::get<0>(getY_Scale()) * topMax;
	float tempAct8 = std::get<0>(getY_Scale()) * bottomMin;

	setAct1(tempAct1);
	setAct2(tempAct2);
	setAct3(tempAct3);
	setAct4(tempAct4);
	setAct5(tempAct5);
	setAct6(tempAct6);
	setAct7(tempAct7);
	setAct8(tempAct8);

}

void Actuator::moveRight() {
	// Move Right:    1-, 2+, 3+, 4+, 5-, 6+, 7+, 8+
	float tempAct1 = std::get<1>(getY_Scale()) * topMin;
	float tempAct2 = std::get<1>(getY_Scale()) * bottomMax;
	float tempAct3 = std::get<1>(getY_Scale()) * topMax;
	float tempAct4 = std::get<1>(getY_Scale()) * bottomMax;
	float tempAct5 = std::get<1>(getY_Scale()) * topMin;
	float tempAct6 = std::get<1>(getY_Scale()) * bottomMax;
	float tempAct7 = std::get<1>(getY_Scale()) * topMax;
	float tempAct8 = std::get<1>(getY_Scale()) * bottomMax;

	setAct1(tempAct1);
	setAct2(tempAct2);
	setAct3(tempAct3);
	setAct4(tempAct4);
	setAct5(tempAct5);
	setAct6(tempAct6);
	setAct7(tempAct7);
	setAct8(tempAct8);

}

void Actuator::moveLeft() {
	// Move Left:     1+, 2-, 3-, 4-, 5+, 6-, 7-, 8-
	float tempAct1 = std::get<0>(getY_Scale()) * topMax;
	float tempAct2 = std::get<0>(getY_Scale()) * bottomMin;
	float tempAct3 = std::get<0>(getY_Scale()) * topMin;
	float tempAct4 = std::get<0>(getY_Scale()) * bottomMin;
	float tempAct5 = std::get<0>(getY_Scale()) * topMax;
	float tempAct6 = std::get<0>(getY_Scale()) * bottomMin;
	float tempAct7 = std::get<0>(getY_Scale()) * topMin;
	float tempAct8 = std::get<0>(getY_Scale()) * bottomMin;

	setAct1(tempAct1);
	setAct2(tempAct2);
	setAct3(tempAct3);
	setAct4(tempAct4);
	setAct5(tempAct5);
	setAct6(tempAct6);
	setAct7(tempAct7);
	setAct8(tempAct8);

}

void Actuator::moveCCW() {
	// Turn CCW:      1+, --, 3-, --, 5-, --, 7+, --
	float tempAct1 = std::get<0>(getY_Scale())* topMax;
	float tempAct2 = 0.0;
	float tempAct3 = std::get<0>(getY_Scale())* topMin;
	float tempAct4 = 0.0;
	float tempAct5 = std::get<0>(getY_Scale())* topMin;
	float tempAct6 = 0.0;
	float tempAct7 = std::get<0>(getY_Scale())* topMax;
	float tempAct8 = 0.0;

	setAct1(tempAct1);
	setAct2(tempAct2);
	setAct3(tempAct3);
	setAct4(tempAct4);
	setAct5(tempAct5);
	setAct6(tempAct6);
	setAct7(tempAct7);
	setAct8(tempAct8);

}

void Actuator::moveCW() {
	// Turn CW:       1-, --, 3+, --, 5+, --, 7-, --
	float tempAct1 = std::get<1>(getY_Scale()) * topMin;
	float tempAct2 = 0.0;
	float tempAct3 = std::get<1>(getY_Scale()) * topMax;
	float tempAct4 = 0.0;
	float tempAct5 = std::get<1>(getY_Scale()) * topMax;
	float tempAct6 = 0.0;
	float tempAct7 = std::get<1>(getY_Scale()) * topMin;
	float tempAct8 = 0.0;

	setAct1(tempAct1);
	setAct2(tempAct2);
	setAct3(tempAct3);
	setAct4(tempAct4);
	setAct5(tempAct5);
	setAct6(tempAct6);
	setAct7(tempAct7);
	setAct8(tempAct8);

}
