#include "../IMU/IMU.hpp"
#include "../HeightSensor/HeightSensor.hpp"

/**
 * @brief Main pod class
 * 
 */
class Pod {
    
public:
    /**
     * @brief Imu class ref
     * 
     */
    IMU imu;
    /**
     * @brief Height ensor class ref
     * 
     */
    HeightSensor height_sensor;

    /**
     * @brief Construct a new Pod object
     * 
     */
    Pod() : imu({1f,1f,1f}), height_sensor(2);

    /**
     * @brief Runs tests
     * 
     */
    void tests() {
        imu.set_x_acel_value(1.0f);
        height_sensor.get_height();
    }
};