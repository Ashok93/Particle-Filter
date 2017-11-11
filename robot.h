#ifndef ROBOT_H
#define ROBOT_H

#include<iostream>
#include<vector>

class Robot {
public:
    // inital x,y position and orientation
    Robot(double x, double y, double orientation, double world_size = 100);

    // forward noise, turn noise, sensor noise
    void set_noise(double f_noise, double t_noise, double s_noise);

    // set new position for the robot
    void set_pose(double new_x, double new_y, double new_orientation);

    // move the robot (turn and move distance)
    void move(double turn, double forward);

    //check if robot in bound of world. If not throw exception.
    bool check_in_world_bounds(double new_x, double new_y, double new_orientation);

    // get the current position and orientation of the robot
    std::vector<double> get_pose();

    //prints current pose
    void print_curr_pose();

private:
    double x;
    double y;
    double orientation;
    double world_size;
    double f_noise;
    double t_noise;
    double s_noise;
    const double PI  =3.141592653589793238463;
};

#endif
