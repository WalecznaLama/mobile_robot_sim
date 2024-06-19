#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include "grid.hpp"

class Gui {
public:
    Gui(int n_rows, int n_cols, int cellSize);

    void drawGrid(SDL_Renderer* renderer);
    void drawRobot(SDL_Renderer* renderer, int x, int y);
    void drawObstacles(SDL_Renderer* renderer, const std::vector<std::vector<int>>& grid);
    void drawPath(SDL_Renderer* renderer, const std::vector<Grid::Point>& path);

private:
    int _n_rows, _n_cols, _cellSize;
};

#endif // GUI_HPP
