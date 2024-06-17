#include "robot.hpp"

Robot::Robot(int startX, int startY) : x(startX), y(startY) {}

void Robot::moveUp() { if (x > 0) x--; }
void Robot::moveDown() { if (x < ROWS - 1) x++; }
void Robot::moveLeft() { if (y > 0) y--; }
void Robot::moveRight() { if (y < COLS - 1) y++; }
