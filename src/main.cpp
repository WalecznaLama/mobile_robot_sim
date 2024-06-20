#include <iostream>
#include "astar.hpp"
#include "dijkstra.hpp"
#include "sdl_setup.hpp"
#include "gui.hpp"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1200;

std::unique_ptr<IPathfinder> createPathfinder(const std::string& type, const Grid& grid) {
    if (type == "A*") {
        return std::make_unique<AStar>(grid);
    } else if (type == "Dijkstra") {
        return std::make_unique<Dijkstra>(grid);
    } else {
        throw std::invalid_argument("Unknown pathfinding type.");
    }
}

int main() {
    std::string grid_csv_filename = "../resources/grid_50x50.csv"; // Path relative to build directory
    Grid grid(grid_csv_filename);

    auto aStarPathfinder = createPathfinder("A*", grid);
    auto dijkstraPathfinder = createPathfinder("Dijkstra", grid);

    const int CELL_SIZE = SCREEN_WIDTH / grid.getCols(); // Calculate cell size based on grid dimensions
    Gui gui(grid.getRows(), grid.getCols(), CELL_SIZE);
    SDLSetup sdlSetup(SCREEN_WIDTH, SCREEN_HEIGHT, CELL_SIZE);
    SDL_Renderer* renderer = sdlSetup.getRenderer();

    Grid::Point a_star_point(0, 0);   // Starting position of the a_star robot
    Grid::Point dijkstra_point(0, 0); // Starting position of the dijkstra robot

    Grid::Point goal;

    std::vector<Grid::Point> a_star_path = aStarPathfinder->findPath(a_star_point, goal);
    std::vector<Grid::Point> dijkstra_path = dijkstraPathfinder->findPath(dijkstra_point, goal);
    size_t a_star_path_index(0), dijkstra_path_index(0);

    bool quit = false;
    while (!quit) {
        Grid::Point eventOutput;
        int eventResult = sdlSetup.processEvents(eventOutput.x, eventOutput.y);
        if (eventResult == -1) {
            quit = true;  // Exit if the quit event is detected
        } else if (eventResult == 1) { // Set new goal and recalculate path
            if (grid.isCellFree(eventOutput)){
                goal = eventOutput;
                a_star_path = aStarPathfinder->findPath(a_star_point, goal);
                a_star_path_index = 0;
                dijkstra_path = dijkstraPathfinder->findPath(dijkstra_point, goal);
                dijkstra_path_index = 0;
            } else std::cout << "The selected cell is occupied. Ignoring the goal...\n" << std::flush;

        } else if (eventResult == 2) {
            grid.changeOccupancy(eventOutput);  // Toggle occupancy at the specified cell
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Black background
        SDL_RenderClear(renderer);
        gui.drawGrid(renderer);
        gui.drawObstacles(renderer, grid.getGrid());

        gui.drawPath(renderer, {a_star_path, dijkstra_path});

        if (a_star_path_index < a_star_path.size()) {
            a_star_point = a_star_path[a_star_path_index];  // Update robot's position along the path - A*
            a_star_path_index++;
        }

        if (dijkstra_path_index < dijkstra_path.size()) {
            dijkstra_point = dijkstra_path[dijkstra_path_index];  // Update robot's position along the path - Dijkstra
            dijkstra_path_index++;
        }

        gui.drawRobot(renderer, {a_star_point, dijkstra_point});

        SDL_RenderPresent(renderer);
        SDL_Delay(200); // Delay to visualize movement
    }

    return 0;
}
