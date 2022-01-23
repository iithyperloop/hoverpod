#pragma once

class HeightSensor {
    float height;
public:
    HeightSensor(float initial_height);

    float get_height();

    void set_height(float new_height);
};