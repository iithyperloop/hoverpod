#include "Hoverpod/GUI/GUI.hpp"
#include "Hoverpod/IMU/IMU.hpp"

int main() {
    std::thread t([ ] {
        init_gui();
    });
    t.detach();

    IMU imu;
    while (true) {
        imu.do_imu();
    }
    return 1;
}
