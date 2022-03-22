#ifndef KALMANFILTER_H_INCLUDED
#define KALMANFILTER_H_INCLUDED

class KalmanFilter {


        int updates;
        double total_calculated_position;
        double average_Distance_Disparity;
        double noise_calculated[100][100];

    public:

        KalmanFilter();

        KalmanFilter(double initialSpeed, double initialAcceleration);

        double get_total_calculated_position();

        double get_average_Distance_Disparity();

        double measurement_update(double newSpeed, double newAcceleration, double timeFrame);

        double calculating_noise(double calculatedposition);
};

#endif // KALMANFILTER_H_INCLUDED
