#include <iostream>
#include <vector>
#include "robot.hpp"
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

    Robot robot(0, 0);
    int goalX = 9, goalY = 9;

    std::vector<Point> path = aStar(robot.x, robot.y, goalX, goalY);

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
        if (pathIndex < path.size()) {
            robot.x = path[pathIndex].x;
            robot.y = path[pathIndex].y;
            pathIndex++;
        }
        drawRobot(renderer, robot.x, robot.y, CELL_SIZE);

        SDL_RenderPresent(renderer);
        SDL_Delay(200); // Delay to visualize robot movement
    }

    return 0;
}
