#include <iostream>
#include <vector>
#include "grid.hpp"
#include "astar.hpp"
#include "sdl_setup.hpp"
#include "gui.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int CELL_SIZE = SCREEN_WIDTH / COLS;

int main() {
    SDLSetup sdlSetup(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Renderer* renderer = sdlSetup.getRenderer();

    Point start_point(0, 0);
    int goalX = 9, goalY = 9;

    std::vector<Point> path = aStar(start_point.x, start_point.y, goalX, goalY);

    bool quit = false;
    SDL_Event e;
    size_t pathIndex = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        drawGrid(renderer, CELL_SIZE, ROWS, COLS);
        drawObstacles(renderer, CELL_SIZE);
        drawPath(renderer, path, CELL_SIZE);
        if (pathIndex < path.size()) {
            start_point.x = path[pathIndex].x;
            start_point.y = path[pathIndex].y;
            pathIndex++;
        }
        drawRobot(renderer, start_point.x, start_point.y, CELL_SIZE);

        SDL_RenderPresent(renderer);
        SDL_Delay(200); // Delay to visualize movement
    }

    return 0;
}
