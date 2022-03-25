#include <chrono>
#include "IMU/IMU.hpp"
#include "Threading/Threading.hpp"

[[noreturn]] void kalman_filter(std::atomic<double>& val) {
	while (true) {
		std::cout << "Side thread: We executed!\n" << std::endl;
		const auto orig_val = val.load();
		val.store(orig_val + 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main() {
	Hyperloop::Thread<double> KalmanFilter(kalman_filter, 0);
	KalmanFilter.run_synchronously();
	while (true) {
		const double val = KalmanFilter.get();
		printf("Main thread: %f\n", val);
		if (val == 100000.0f)
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
    return 1;
}
