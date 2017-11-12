#include<iostream>
#include<vector>
#include "particle_filter.h"
#include"robot.h"

double ParticleFilter::measurement_probability(std::vector<double> measurement,
                                        std::vector<double> actual_measurement,
                                        double noise)
{
    double prob = 1.0;
    for(int i=0; i<measurement.size(); i++)
    {
        prob *= ParticleFilter::gaussian(measurement[i], noise, actual_measurement[i]);
    }

    return prob;
}

std::vector<Robot> ParticleFilter::resampling_wheel(std::vector<double> measurement_probabilities,
                                                    std::vector<Robot> particles)
{

}

double ParticleFilter::gaussian(double mu, double sigma, double x)
{
    double numerator = (std::pow((mu - x), 2)) / (std::pow(sigma, 2) / 2);
    double denominator = std::sqrt(2 * 3.1415926535897 * std::pow(sigma, 2));

    return std::exp(- (numerator / denominator));
}
