#include<iostream>
#include<vector>
#include<string>
#include<math.h>

#include "robot.h"

Robot::Robot(double _x, double _y, double _orientation, int _world_size, std::vector<std::vector<double>> _landmarks)
{
    x = _x;
    y = _y;
    orientation = _orientation;
    world_size = _world_size;
    landmarks = _landmarks;
    srand (time(NULL));
    generator.seed(rand()%100);
}

std::vector<double> Robot::get_pose()
{
    std::vector<double> curr_pos = {x, y, orientation};
    return curr_pos;
}

void Robot::set_pose(double new_x, double new_y, double new_orientation)
{
    Robot::check_in_world_bounds(new_x, new_y, new_orientation);
    x = new_x;
    y = new_y;
    orientation = new_orientation;
}

void Robot::set_noise(double _f_noise, double _t_noise, double _s_noise)
{
    f_noise = _f_noise;
    t_noise = _t_noise;
    s_noise = _s_noise;
}

void Robot::move(double turn, double forward)
{
    // Add turn noise and turn the robot
    std::normal_distribution<double> t_dis(0.0, t_noise);
    double t_noise_value = t_dis(generator);
    orientation = orientation + turn + t_noise_value;
    orientation = fmod(orientation,(2 * PI));

    // Add move noise and move the robot
    std::normal_distribution<double> f_dis(0.0, f_noise);
    double f_noise_value = f_dis(generator);
    x = x + cos(orientation) * (forward + f_noise_value);
    y = y + sin(orientation) * (forward + f_noise_value);

    x = fmod(x, world_size);
    y = fmod(y, world_size);
}

std::vector<double> Robot::sense_landmarks(bool add_s_noise)
{
    std::vector<double> distances;

    for(auto const &landmark: landmarks)
    {
        double distance;
        distance = std::sqrt(std::pow(x-landmark[0], 2) + std::pow(y-landmark[1], 2));

        if(add_s_noise)
        {
            // adding sensor noise
            std::normal_distribution<double> s_dis(0.0, s_noise);
            double s_noise_value = s_dis(generator);
            distance += s_noise_value;
        }

        distances.push_back(distance);
    }

    return distances;
}

void Robot::print_curr_pose()
{
    std::cout << "The X position is " << x << std::endl;
    std::cout << "The Y position is " << y << std::endl;
    std::cout << "The Orientation is " << orientation << std::endl;
}

void Robot::print_curr_dis_to_landmarks()
{
    std::vector<double> landmark_dis = Robot::sense_landmarks();

    std::cout << "The landmark distances.." << std::endl;
    for(auto distance: landmark_dis)
    {
        std::cout << distance << std::endl;
    }
}

bool Robot::check_in_world_bounds(double new_x, double new_y, double new_orientation)
{
    if(new_x < 0 || new_x >= world_size)
    {
        throw std::invalid_argument("The X value is out of bound of the world defined!!");
    }
    else if(new_y < 0 || new_y >= world_size)
    {
        throw std::invalid_argument("The Y value is out of bound of the world defined!!");
    }
    else if(new_orientation < 0 || new_orientation >= 2*PI)
    {
        throw std::invalid_argument("The orientation should be between 0 to 2*pi");
    }

    return true;
}
