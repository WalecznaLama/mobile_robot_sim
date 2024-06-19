#ifndef SDL_SETUP_HPP
#define SDL_SETUP_HPP

#include <SDL2/SDL.h>
#include <iostream>

class SDLSetup {
public:
    SDLSetup(int screenWidth, int screenHeight, int cellSize);
    ~SDLSetup();
    SDL_Renderer* getRenderer();
    int processEvents(int &xCell, int &yCell);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int _cellSize;
};

#endif // SDL_SETUP_HPP
