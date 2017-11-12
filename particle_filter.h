#include<iostream>
#include<string>
#include<vector>
#include "robot.h"

class ParticleFilter {
public:
    double measurement_probability(std::vector<double> measurement,
                                   std::vector<double> actual_measurement,
                                   double noise);

    std::vector<Robot> resampling_wheel(std::vector<double> measurement_probabilities,
                                        std::vector<Robot> particles);

    double gaussian(double mu, double sigma, double x);
};
