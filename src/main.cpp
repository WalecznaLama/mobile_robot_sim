#include <iostream>
#include "robot.hpp"
#include "grid.hpp"
#include "astar.hpp"

int main() {
    Robot robot(0, 0);
    int goalX = 9, goalY = 9;

    std::vector<Point> path = aStar(robot.x, robot.y, goalX, goalY);

    for (const auto& point : path) { printGrid(point.x, point.y); }

    if (!path.empty() && path.back() == Point(goalX, goalY)) { std::cout << "Reached the goal!" << std::endl; } 
    else { std::cout << "No path found!" << std::endl; }

    return 0;
}
