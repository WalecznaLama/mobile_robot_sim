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

// Function to print the grid with the robot's current position
void printGrid(int robotX, int robotY) {
    system("clear"); // Clear the console screen
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == robotX && j == robotY) {
                std::cout << "R "; // Print the robot's position
            } else if (grid[i][j] == 1) {
                std::cout << "X "; // Print an obstacle
            } else {
                std::cout << ". "; // Print a free space
            }
        }
        std::cout << std::endl;
    }
    // Pause for 500 milliseconds to create an animation effect
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
