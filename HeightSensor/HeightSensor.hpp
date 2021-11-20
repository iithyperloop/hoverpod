/**
 * @brief Class to get height from the height sensor
 * 
 */
class HeightSensor {
    float height;
public:
    /**
     * @brief Construct a new Height Sensor with a given height
     * 
     * @param initial_height Initial height value for sensor
     */
    HeightSensor(float initial_height);
    /**
     * @brief Get the current height from the sensor
     * 
     * @return float Current height
     */
    float get_height();
    /**
     * @brief Set the new height for the sensor
     * 
     * @param new_height New height for the sensor 
     */
    void set_height(float new_height);
};