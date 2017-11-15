#include<iostream>
#include<vector>
#include<random>
#include<algorithm>

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
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    std::vector<Robot> filtered_particles;
    double index = dist(mt) * particles.size();
    double beta = 0.0;

    double max_measurement_prob = *std::max_element(measurement_probabilities.begin(), measurement_probabilities.end());

    for(int i=0; i<particles.size(); ++i)
    {
        beta += dist(mt) * 2 * max_measurement_prob;

        while(beta > measurement_probabilities[index])
        {
            beta -= measurement_probabilities[index];
            index = fmod((index + 1),particles.size());
        }

        filtered_particles.push_back(particles[index]);
    }

    return filtered_particles;
}

double ParticleFilter::gaussian(double mu, double sigma, double x)
{
    double numerator = (std::pow((mu - x), 2)) / (std::pow(sigma, 2) / 2);
    double denominator = std::sqrt(2 * 3.1415926535897 * std::pow(sigma, 2));

    return std::exp(- (numerator / denominator));
}
