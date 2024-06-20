#include "gui.hpp"

Gui::Gui(int n_rows, int n_cols, int cellSize) : _n_rows(n_rows), _n_cols(n_cols), _cellSize(cellSize) {}

void Gui::drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i <= _n_rows; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * _cellSize, _n_rows * _cellSize, i * _cellSize);
    }
    for (int i = 0; i <= _n_cols; ++i) {
        SDL_RenderDrawLine(renderer, i * _cellSize, 0, i * _cellSize, _n_cols * _cellSize);
    }
}

void Gui::drawRobot(SDL_Renderer* renderer, const std::vector<Grid::Point>& points) { // TODO solve the overlap problem 
    int color_index = 0;
    for (const auto& point : points) {
        SDL_SetRenderDrawColor(renderer,
                       _draw_colors[color_index % _draw_colors.size()].r,
                       _draw_colors[color_index % _draw_colors.size()].g,
                       _draw_colors[color_index % _draw_colors.size()].b,
                       SDL_ALPHA_OPAQUE);
        SDL_Rect rect = {point.y * _cellSize, point.x * _cellSize, _cellSize, _cellSize};
        SDL_RenderFillRect(renderer, &rect);
        color_index++;
    }
}

void Gui::drawObstacles(SDL_Renderer* renderer, const std::vector<std::vector<int>>& grid) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < _n_rows; ++i) {
        for (int j = 0; j < _n_cols; ++j) {
            if (grid[i][j] == 1) {
                SDL_Rect rect = {j * _cellSize, i * _cellSize, _cellSize, _cellSize};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Gui::drawPath(SDL_Renderer* renderer, const std::vector<std::vector<Grid::Point>>& paths) { // TODO solve the overlap problem 
    int dot_size = _cellSize / 5;
    int color_index = 0;
    for (const auto& path : paths) {
        SDL_SetRenderDrawColor(renderer,
                               _draw_colors[color_index % _draw_colors.size()].r,
                               _draw_colors[color_index % _draw_colors.size()].g,
                               _draw_colors[color_index % _draw_colors.size()].b,
                               SDL_ALPHA_OPAQUE);
        for (const auto& point : path) {
            SDL_Rect rect = {(point.y * _cellSize) + _cellSize / 2 - dot_size / 2, (point.x * _cellSize) + _cellSize / 2 - dot_size / 2, dot_size, dot_size};
            SDL_RenderFillRect(renderer, &rect);
        }
        color_index++;
    }
}
