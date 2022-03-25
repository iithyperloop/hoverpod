#include <iostream>
#include <cmath>
#include "KalmanFilter.hpp"

KalmanFilter::KalmanFilterException::KalmanFilterException(const std::string m) {
    message = "KalmanFilterException: " + m;
}

const char *KalmanFilter::KalmanFilterException::what() const noexcept {
    return message.c_str();
}

//default constructor does nothing but make an object and initiate variables

KalmanFilter::KalmanFilter() : updates(0), total_calculated_position(0), average_Distance_Disparity(0)  {}

//KalmanFilter given 3 parameters accounts for initial velocity
KalmanFilter::KalmanFilter(double initialSpeed, double initialAcceleration) {
    //measurement_update(initialSpeed, initialAcceleration, 0);
}

//total calculated position accessor
double KalmanFilter::get_total_calculated_position() {
    return total_calculated_position;
}

//average distance disparity accessor
double KalmanFilter::get_average_Distance_Disparity() {
    return average_Distance_Disparity;
}

//measurement update method
double KalmanFilter::measurement_update(double newSpeed, double newAcceleration= 0, double timeFrame = 5.0) {
    //newSpeed will be given from the Motors using getSpeed() method
    double v = newSpeed;
    //newAcceleration given from the IMU using get_x_acel() and get_y_acel method
    double a = newAcceleration;
    //time will be how long the Kalman will incremently calculate the position
    double t = timeFrame;
    //Calculating the position of the hoverboard given
    double calculatedPosition = (v*t) + (0.5 * (a) * pow(t, 2.0));

    //Updating the number of updates on run
    updates += 1;

    //Updating the total position on the Kalman Filter run
    total_calculated_position += calculatedPosition;
    average_Distance_Disparity = (total_calculated_position / updates);

    return calculatedPosition;
}

//KalmanFilter noise calculation throughout entire run
double KalmanFilter::calculating_noise(double calculatedPosition) {
    //Creating array of measurement history
    if (updates == 0) {
        noise_calculated[updates][0] = updates;
        noise_calculated[updates][1] = 0;
    }
    else {
        noise_calculated[updates][0] = updates;
        noise_calculated[updates][1] = abs(average_Distance_Disparity - (total_calculated_position - (total_calculated_position - calculatedPosition)));
    }

    return noise_calculated[updates][1];


    /*if (updates == 0) {
        noise_calculated[updates][0] = updates;
        noise_calculated[updates][1] = 0;
    }
    else {
        noise_calculated[updates][0] = updates;
        noise_calculated[updates][1] = abs(average_Distance_Disparity - (total_calculated_position - (total_calculated_position - calculatedPosition)));
    }*/
}