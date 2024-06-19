#include "gui.hpp"

Gui::Gui(int n_rows, int n_cols, int cellSize) : _n_rows(n_rows), _n_cols(n_cols), _cellSize(cellSize) {}

void Gui::drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i <= _n_rows; ++i) SDL_RenderDrawLine(renderer, 0, i * _cellSize, _n_rows * _cellSize, i * _cellSize);
    for (int i = 0; i <= _n_cols; ++i) SDL_RenderDrawLine(renderer, i * _cellSize, 0, i * _cellSize, _n_cols * _cellSize);
}

void Gui::drawRobot(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect rect;
    rect.x = y * _cellSize; // NOTE x/y swapped
    rect.y = x * _cellSize;
    rect.w = _cellSize;
    rect.h = _cellSize;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void Gui::drawObstacles(SDL_Renderer* renderer,  const std::vector<std::vector<int>>& grid) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < _n_rows; ++i) {
        for (int j = 0; j < _n_cols; ++j) {
            if (grid[i][j] == 1) {
                SDL_Rect rect;
                rect.x = j * _cellSize; // NOTE x/y swapped
                rect.y = i * _cellSize;
                rect.w = _cellSize;
                rect.h = _cellSize;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Gui::drawPath(SDL_Renderer* renderer, const std::vector<Grid::Point>& path) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int dot_size = _cellSize/5;
    for (const auto& point : path) { // NOTE x/y swapped
        SDL_Rect rect = { (point.y * _cellSize) + _cellSize/2 - dot_size/2,
                          (point.x * _cellSize) + _cellSize/2 - dot_size/2,
                          dot_size, dot_size };
        SDL_RenderFillRect(renderer, &rect);
    }
}
