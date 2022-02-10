#include "HeightSensor/HeightSensor.hpp"
#include "IMU/IMU.hpp"
#include "Motor/Motor.hpp"
#include "Actuator/Actuator.hpp"
#include "Threading/Threading.hpp"
#include <chrono>

void kalman_filter(std::atomic<double>& val) {
	while (true) {
		std::cout << "Side thread: We executed!\n" << std::endl;
		const auto orig_val = val.load();
		val.store(orig_val + 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main() {
	Hyperloop::Thread<double> KalmanFilter(kalman_filter, 0);
	KalmanFilter.run_asynchronously();
	while (true) {
		double val = KalmanFilter.get();
		printf("Main thread: %f\n", val);
		if (val == 100000)
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
    return 1;
}