#include "Hoverpod/GUI/GUI.hpp"
#include "Hoverpod/IMU/IMU.hpp"

int main() {
    // https://en.cppreference.com/w/cpp/thread/thread
    // [] is lambda declaration (inline anonymous function)
    std::thread t([] { // [] {} == lambda 
        init_gui(); // do gui (which has loop inside of it)
    });
    t.detach(); // run seperate from main thread

    IMU imu; // instantiate imu object
    while (true) { // run forever because if main thread exists, side thread exists
        imu.do_imu(); // do imu
    }
    return 1; // success (should never reach this)
}
