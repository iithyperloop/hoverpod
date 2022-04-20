#include "Hoverpod/GUI/GUI.hpp"
#include <Windows.h>
#include "Hoverpod/IMU/IMU.hpp"

int main() {
	IMU imu;
	imu.do_imu();
    return 1;
}
