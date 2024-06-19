#ifndef SDL_SETUP_HPP
#define SDL_SETUP_HPP

#include <SDL2/SDL.h>
#include <iostream>

// Handles setup and management of an SDL window and renderer.
class SDLSetup {
public:
    // Initializes SDL, creating a window and renderer based on the specified dimensions.
    SDLSetup(int screenWidth, int screenHeight, int cellSize);
    // Cleans up SDL resources.
    ~SDLSetup();

    // Returns a pointer to the SDL renderer for drawing.
    SDL_Renderer* getRenderer();

    // Processes SDL events and updates cell coordinates based on user input.
    // Returns - 0: No event; -1: exit; 1: set goal; 2: cell toggle occupancy.
    int processEvents(int &xCell, int &yCell);

private:
    SDL_Window* window;      // The main window
    SDL_Renderer* renderer;  // The renderer for drawing
    int _cellSize;           // Size of each cell in the grid, used for coordinate translation
};

#endif // SDL_SETUP_HPP
