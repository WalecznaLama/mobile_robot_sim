
# MobileRobotSim Project

This project simulates a mobile robot navigating through a grid using the A* and Dijkstra pathfinding algorithm, visualized with SDL.

## Features

- Grid generation from a CSV file.
- Dynamic pathfinding with A* and Dijkstra algorithm.
- Interactive GUI using SDL2 for real-time simulation control.
- Obstacle placement and goal setting through mouse interaction.

## Project Structure

- **include/**: Header files.
- **src/**: Source files including the main program.
- **resources/**: Resource files like grid configurations.
- **CMakeLists.txt**: Build configuration file.
- **README.md**: This project documentation.

## Prerequisites

Ensure you have the following installed:
- SDL2
- CMake (version 3.10 or higher)
- A C++17 compliant compiler

## Building the Project

To build the project, follow these steps:

1. Navigate to the project directory.
2. Create a build directory and enter it:
   ```bash
   mkdir build && cd build
   ```
3. Configure the project with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   make
   ```

## Running the Project

After building, you can run the executable within the build directory:

```bash
./mobile_robot_sim
```

## Interactions

- **Set Goal**: Click on the desired cell to move the goal to that location.
- **Toggle Obstacles**: Press 'T' and click on a cell to add/remove obstacles.