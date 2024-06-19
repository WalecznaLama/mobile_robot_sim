#ifndef GUI_HPP
#define GUI_HPP

#include "grid.hpp"
#include <SDL2/SDL.h>

// Manages graphical rendering of a grid, robot, obstacles, and paths using SDL.
class Gui {
public:
    // Constructor to initialize the grid dimensions and cell size.
    Gui(int n_rows, int n_cols, int cellSize);

    // Draws the grid using the provided SDL renderer.
    void drawGrid(SDL_Renderer* renderer);

    // Draws the robot at position (x, y) using the provided SDL renderer.
    void drawRobot(SDL_Renderer* renderer, int x, int y);

    // Draws obstacles on the grid based on the grid's state using the provided SDL renderer.
    void drawObstacles(SDL_Renderer* renderer, const std::vector<std::vector<int>>& grid);

    // Draws the path using the provided SDL renderer.
    void drawPath(SDL_Renderer* renderer, const std::vector<Grid::Point>& path);

private:
    int _n_rows, _n_cols, _cellSize;  // Grid dimensions and cell size
};

#endif // GUI_HPP
