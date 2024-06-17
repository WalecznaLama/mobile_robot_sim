#include "gui.hpp"

void drawGrid(SDL_Renderer* renderer, int cellSize, int rows, int cols) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i <= rows; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * cellSize, rows * cellSize, i * cellSize);
    }
    for (int i = 0; i <= cols; ++i) {
        SDL_RenderDrawLine(renderer, i * cellSize, 0, i * cellSize, cols * cellSize);
    }
}

void drawRobot(SDL_Renderer* renderer, int x, int y, int cellSize) {
    SDL_Rect rect;
    rect.x = x * cellSize;
    rect.y = y * cellSize;
    rect.w = cellSize;
    rect.h = cellSize;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void drawObstacles(SDL_Renderer* renderer, int cellSize) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j] == 1) {
                SDL_Rect rect;
                rect.x = i * cellSize;
                rect.y = j * cellSize;
                rect.w = cellSize;
                rect.h = cellSize;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}