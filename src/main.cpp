#include <iostream>
#include <vector>
#include "grid.hpp"
#include "astar.hpp"
#include "sdl_setup.hpp"
#include "gui.hpp"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1200;

int main() {
    std::string grid_csv_filename = "../resources/grid_50x50.csv"; // Path relative to build directory
    Grid grid(grid_csv_filename);
    AStar aStar(grid);

    const int CELL_SIZE = SCREEN_WIDTH / grid.getCols(); // Calculate cell size based on grid dimensions
    Gui gui(grid.getRows(), grid.getCols(), CELL_SIZE);
    SDLSetup sdlSetup(SCREEN_WIDTH, SCREEN_HEIGHT, CELL_SIZE);
    SDL_Renderer* renderer = sdlSetup.getRenderer();

    Grid::Point robot_point(0, 0); // Starting position of the robot
    Grid::Point goal(2, 2);        // Initial goal
    std::vector<Grid::Point> path = aStar.findPath(robot_point.x, robot_point.y, goal.x, goal.y);
    size_t pathIndex = 0;

    bool quit = false;
    while (!quit) {
        Grid::Point eventOutput(-1, -1);
        int eventResult = sdlSetup.processEvents(eventOutput.x, eventOutput.y);
        if (eventResult == -1) {
            quit = true;  // Exit if the quit event is detected
        } else if (eventResult == 1) {
            goal = eventOutput;  // Set new goal and recalculate path
            path = aStar.findPath(robot_point.x, robot_point.y, goal.x, goal.y);
            pathIndex = 0;
        } else if (eventResult == 2) {
            grid.changeOccupancy(eventOutput);  // Toggle occupancy at the specified cell
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        gui.drawGrid(renderer);
        gui.drawObstacles(renderer, grid.getGrid());
        gui.drawPath(renderer, path);

        if (pathIndex < path.size()) {
            robot_point.x = path[pathIndex].x;  // Update robot's position along the path
            robot_point.y = path[pathIndex].y;
            pathIndex++;
        }

        gui.drawRobot(renderer, robot_point.x, robot_point.y);
        SDL_RenderPresent(renderer);
        SDL_Delay(200); // Delay to visualize movement
    }

    return 0;
}
