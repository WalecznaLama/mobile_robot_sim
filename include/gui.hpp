#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include "grid.hpp"
#include "robot.hpp"

void drawGrid(SDL_Renderer* renderer, int cellSize, int rows, int cols);
void drawRobot(SDL_Renderer* renderer, int x, int y, int cellSize);
void drawObstacles(SDL_Renderer* renderer, int cellSize);

#endif // GUI_HPP
