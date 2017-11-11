#include<iostream>
#include<vector>
#include<string>
#include<math.h>

#include "robot.h"

Robot::Robot(double _x, double _y, double _orientation, double _world_size)
{
    x = _x;
    y = _y;
    orientation = _orientation;
    world_size = _world_size;
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
    //turn the robot
    orientation = orientation + turn;
    orientation = fmod(orientation,(2 * PI));

    //move the robot
    x = x + cos(orientation) * forward;
    y = y + sin(orientation) * forward;
}

void Robot::print_curr_pose()
{
    std::cout << "The X position is " << x << std::endl;
    std::cout << "The Y position is " << y << std::endl;
    std::cout << "The Orientation is " << orientation << std::endl;
}

bool Robot::check_in_world_bounds(double new_x, double new_y, double new_orientation) {
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
