#include "grid.hpp"
#include <iostream>
#include <thread>
#include <chrono>

// Define the grid with obstacles (1) and free spaces (0)
int grid[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void changeOccupancy(const Point &cell) { grid[cell.x][cell.y] ^= 1; } // Toggle between 1 and 0 using XOR
