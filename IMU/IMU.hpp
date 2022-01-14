#pragma once
#include <vector>
#include <iostream>

/**
 * @brief Class for an interface to the IMU sensor
 * @todo implement failsafe
 */
class IMU {
    /**
     * @brief Structure to help manage acceleration data
     */
    std::vector<float> read_sensor_data();
public:
    struct acceleration_data {
        /**
         * @brief Acceleration X value
         */
        float x;
        /**
         * @brief Acceleration Y value
         */
        float y;
        /**
         * @brief Acceleration Z value
         */
        float z;

        /**
         * @brief Equals comparison for acceleration data
         * 
         * @param other 
         * @return true They are equal
         * @return false They are not equal
         */
        bool operator==(acceleration_data const& other) const { return other.x == x && other.y == y && other.z == z; }

        // allow us to cout << get_acel_values() for debugging and testing
        /**
         * @brief std::ostream << operator friend, allows us to cout acceleration_data
         * 
         * @param output outstream to print to
         * @param dat acceleration_data to print
         * @return std::ostream& 
         */
        friend std::ostream &operator<<(std::ostream &output, const acceleration_data& dat) { 
            output << "{" << dat.x <<  ", " << dat.y << ", " << dat.z << "}";
            return output;            
        }
    } acel_values;

    /**
     * @brief Construct a new IMU object
     * 
     * @param start The starting accelration data, used for debugging
     */
    IMU(const acceleration_data start);

    /**
     * @brief Construct a new IMU object
     * 
     */
    IMU();

    /**
     * @brief Get the current acceleration data
     * 
     * @return acceleration_data Current acceleration data from the sensor
     */
    acceleration_data get_acel_values();

    /**
     * @brief Get the acelleration data x value
     * 
     * @return float Current acceleration data x value
     */
    float get_x_acel_value();

     /**
     * @brief Get the acelleration data y value
     * 
     * @return float Current acceleration data y value
     */
    float get_y_acel_value();

     /**
     * @brief Get the acelleration data z value
     * 
     * @return float Current acceleration data z value
     */
    float get_z_acel_value();

    /**
     * @brief Set the current acceleration data values
     * 
     * @param val New acceleration data
     */
    void set_acel_values(const acceleration_data val);

    /**
     * @brief Set the acelleration data x value
     * 
     * @return float New acceleration data x value
     */
    void set_x_acel_value(const float val);

    /**
     * @brief Set the acelleration data y value
     * 
     * @return float New acceleration data y value
     */
    void set_y_acel_value(const float val);

    /**
     * @brief Set the acelleration data z value
     * 
     * @return float New acceleration data z value
     */
    void set_z_acel_value(const float val);
};