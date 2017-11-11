#include<iostream>
#include<string>
#include<vector>

#include "robot.h"

int main()
{
    const double PI  =3.141592653589793238463;
    Robot robot(0, 0, 0);
    robot.set_pose(90,90, PI/4);
    //robot.move(PI/2, 20);
    //std::vector<double> current_pose = robot.get_pose();
    robot.print_curr_pose();
    return 0;
}
