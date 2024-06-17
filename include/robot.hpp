#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "grid.hpp"

class Robot {
public:
    int x, y;
    Robot(int startX, int startY);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

#endif // ROBOT_HPP
