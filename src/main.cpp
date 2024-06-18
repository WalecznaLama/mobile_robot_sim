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
    Point goal(9, 9);  // Initial goal
    std::vector<Point> path = aStar(robot_point.x, robot_point.y, goal.x, goal.y);
    size_t pathIndex = 0;

    bool quit = false;

    while (!quit) {
        Point eventOutput(-1, -1);
        int eventResult = sdlSetup.processEvents(eventOutput.x, eventOutput.y, CELL_SIZE);
        if (eventResult == -1) {
            quit = true;
        } else if(eventResult == 1){
            goal = eventOutput;
            path = aStar(robot_point.x, robot_point.y, goal.x, goal.y);  // Recalculate path if goal changed
            pathIndex = 0;
        } else if(eventResult == 2){
            Point cellToToggle = eventOutput;
            changeOccupancy(cellToToggle);
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
