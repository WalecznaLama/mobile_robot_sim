cmake_minimum_required(VERSION 3.10)

project(MobileRobotSim VERSION 1.0 DESCRIPTION "Mobile robot simulation using A* pathfinding")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include)

add_executable(mobile_robot_sim 
    src/main.cpp 
    src/grid.cpp 
    src/astar.cpp 
    src/sdl_setup.cpp 
    src/gui.cpp
)

target_link_libraries(mobile_robot_sim ${SDL2_LIBRARIES})