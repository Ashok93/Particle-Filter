#include<iostream>
#include<string>
#include<vector>

#include "robot.h"

int main()
{
    const double PI  =3.141592653589793238463;
    int world_size = 100;
    std::vector<std::vector<double>> landmark_positions = { {20,20}, {80,80}, {20,80}, {80,20} };
    Robot robot(0, 0, 0, world_size, landmark_positions);
    robot.set_pose(5,5, PI);
    robot.print_curr_dis_to_landmarks();
    robot.set_noise(0.08, 0.08, 0.2);
    robot.move(-PI/2, 40);
    robot.print_curr_dis_to_landmarks();
    robot.print_curr_pose();
    return 0;
}
