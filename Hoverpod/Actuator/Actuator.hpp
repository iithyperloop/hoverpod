#pragma once
#include <tuple>
#include <iostream>

enum class ActuatorStatus
{
    STATUS_OK,
    STATUS_LENGTH_ERROR
};

class Actuator {
    int length;
    float joystickOutput[3];

    float x_in;
	float y_in;
	float z_in;

	float x_scale[2];
	float y_scale[2];
	float z_scale[2];

	float x_scaleL;
	float x_scaleR;
	float y_scaleF;
	float y_scaleB;
	float z_scaleCW;
	float z_scaleCCW;

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
    
public:
    Actuator(int length = 0);

    [[nodiscard]] int GetLength() const;

    void SetLength(int nlength);

    //Getters

    float getX();

    float getY();

    float getZ();

    std::tuple<float, float> getX_Scale();

    std::tuple<float, float> getY_Scale();

    std::tuple<float, float> getZ_Scale();

    float getAct1();

    float getAct2();

    float getAct3();

    float getAct4();

    float getAct5();

    float getAct6();

    float getAct7();

    float getAct8();

    //Setters
    void setX(float joystickOutput[]);

    void setY(float joystickOutput[]);

    void setZ(float joystickOutput[]);

    void setX_Scale(float x_in);

    void setY_Scale(float y_in);

    void setZ_Scale(float z_in);

    void setAct1(float val);

    void setAct2(float val);

    void setAct3(float val);

    void setAct4(float val);

    void setAct5(float val);

    void setAct6(float val);

    void setAct7(float val);

    void setAct8(float val);

    // Movement Methods (not sure what output should be since idk how to get the data to the actuators)
    void moveForward();

    void moveBackward();

    void moveRight();

    void moveLeft();

    void moveCCW();

    void moveCW();

};