#include <iostream>
#include <string_view>
#include "IMU.hpp"

// let's use c++20 it's the new standard! please
#undef assert
template<typename T>
constexpr void assert_s(const T expr_1, const T expr_2, const int line) {
    if (expr_1 != expr_2) {
        std::cerr << "assert failed: " << __FILE__ << ":"
              << line << " ("
              << expr_1 << " != " << expr_2 << ")" << std::endl;
        exit(0xdeadbeef);
    }
}
#define assert(expr_1, expr_2) assert_s<decltype(expr_1)>(expr_1, expr_2, __LINE__)

int main() {
    IMU imu; // default constructor, read from sensor

    IMU imu_1({
        .x = 1.1112f,
        .y = 1.23334f,
        .z = 1.3122f
    });
    // alternatively.. whatever syntax you bozos prefer
    // this constructor will probably only be used for tests anyways
    IMU imu_2({
        1.0f,
        1.2f,
        1.3f
    });

    assert(imu.get_x_acel_value(), 0);
    assert(imu.get_y_acel_value(), 0);
    assert(imu.get_z_acel_value(), 0);

    assert(imu_1.get_x_acel_value(), 1.1112f);
    assert(imu_1.get_y_acel_value(), 1.23334f);
    assert(imu_1.get_z_acel_value(), 1.3122f);

    const IMU::ac_dat dat = {.x = 100.1f, .y = 100.2131f, .z = 1999.22f};
    imu.set_acel_values(dat);

    assert(imu.get_acel_values(), dat);

    std::cout << "Tests passed, Current values:" << std::endl << 
        imu.get_acel_values() << std::endl << imu_1.get_acel_values() <<
        std::endl << imu_2.get_acel_values() << std::endl;
    return 1;
}