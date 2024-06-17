cmake_minimum_required(VERSION 3.10)

# Set project name
project(MobileRobotSim)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include)

# Add the executable
add_executable(mobile_robot_sim src/main.cpp src/robot.cpp src/grid.cpp src/astar.cpp)

