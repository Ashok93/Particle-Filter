#include<iostream>
#include<string>
#include<vector>
#include<random>

#include "robot.h"
#include "particle_filter.h"

int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    const double PI  =3.141592653589793238463;
    int world_size = 100;
    std::vector<std::vector<double>> landmark_positions = { {20,20}, {80,80}, {20,80}, {80,20} };
    Robot robot(0, 0, 0, world_size, landmark_positions);
    robot.set_pose(5,5, PI);
    robot.move(0.1, 5.0);
    robot.print_curr_pose();
    std::vector<double> Z = robot.sense_landmarks();


    int N = 1000;

    std::vector<Robot> robot_particles;

    for(int i=0; i<N; i++)
    {
        Robot r(dist(mt)*world_size, dist(mt)*world_size, dist(mt)*2*PI, world_size, landmark_positions);
        r.set_noise(0.05, 0.05, 5.0);
        r.move(0.1, 5.0);
        robot_particles.push_back(r);
    }

    std::vector<double> measurement_probabilities;

    for(int i=0; i<N; i++)
    {
        std::vector<double> measurements = robot_particles[i].sense_landmarks(false);
        ParticleFilter pf;
        double mp = pf.measurement_probability(measurements, Z, robot_particles[i].s_noise);
        measurement_probabilities.push_back(mp);
    }

    std::cout << "measurement probabilities" << std::endl;
    for(int i=0; i<measurement_probabilities.size(); i++)
    {
        std::cout << measurement_probabilities[i] << std::endl;

        if(measurement_probabilities[i] > 0.5) {
            std::cout << "Very likelyyyyyyyyyyyyyyy with meas prob " << measurement_probabilities[i] <<  std::endl;
            robot_particles[i].print_curr_pose();
        }
    }

    robot.move(-PI/2, 5);
    robot.print_curr_dis_to_landmarks();
    robot.print_curr_pose();
    return 0;
}
