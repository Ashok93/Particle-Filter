cmake_minimum_required (VERSION 2.6)
project (particle_filter)

add_compile_options(-std=c++11)

add_executable(main particle_filter.h particle_filter.cpp robot.h robot.cpp main.cpp)
