cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include)

add_executable(mobile_robot_sim 
    src/main.cpp 
    src/robot.cpp 
    src/grid.cpp 
    src/astar.cpp 
    src/sdl_setup.cpp 
    src/gui.cpp
)

target_link_libraries(mobile_robot_sim ${SDL2_LIBRARIES})