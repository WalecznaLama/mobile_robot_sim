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

    Point robot_point(0, 0);
    int goalX = 9, goalY = 9;  // Initial goal
    std::vector<Point> path = aStar(robot_point.x, robot_point.y, goalX, goalY);
    size_t pathIndex = 0;

    bool quit = false;

    while (!quit) {
        int eventResult = sdlSetup.processEvents(goalX, goalY, CELL_SIZE);
        if (eventResult == 0) {
            quit = true;
        } else if(eventResult == 1){
            path = aStar(robot_point.x, robot_point.y, goalX, goalY);  // Recalculate path only if goal changed
            pathIndex = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        drawGrid(renderer, CELL_SIZE, ROWS, COLS);
        drawObstacles(renderer, CELL_SIZE);
        drawPath(renderer, path, CELL_SIZE);

        if (pathIndex < path.size()) {
            robot_point.x = path[pathIndex].x;
            robot_point.y = path[pathIndex].y;
            pathIndex++;
        }

        drawRobot(renderer, robot_point.x, robot_point.y, CELL_SIZE);

        SDL_RenderPresent(renderer);
        SDL_Delay(200); // Delay to visualize movement
    }

    return 0;
}
