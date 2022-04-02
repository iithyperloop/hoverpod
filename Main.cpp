#include <chrono>
#include "Hoverpod/GUI/GUI.hpp"
#include "Hoverpod/Threading/Threading.hpp"
#include "vn/matrix.h"
#include "vn/vector.h"

[[noreturn]] void kalman_filter(std::atomic<double>& val) {
	while (true) {
		std::cout << "Side thread: We executed!\n" << std::endl;
		const auto orig_val = val.load();
		val.store(orig_val + 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

using namespace vn::math;

void vn_tests() {
	vec3f v1(1.0f, 2.0f, 3.0f);			// An initialized 3 component vector of floats.
	vec3d v2(4.0, 5.0, 6.0);			// An initialized 3 component vector of doubles.
	vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);	// An initialized 4 component vector of floats.
	std::string v1Str = str(v1);
	std::cout << "v1: " << v1Str << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "zero vector: " << vec3f::zero() << std::endl;
	std::cout << "x-direction vector: " << vec3f::unitX() << std::endl;
}

int main() {
	//vn_tests();
	init_gui();
	/*Hyperloop::Thread<double> KalmanFilter(kalman_filter, 0);
	KalmanFilter.run_synchronously();
	while (true) {
		const double val = KalmanFilter.get();
		printf("Main thread: %f\n", val);
		if (val == 100000.0f)
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
    return 1;*/
}
