#ifndef SDL_SETUP_HPP
#define SDL_SETUP_HPP

#include <SDL2/SDL.h>
#include <iostream>

class SDLSetup {
public:
    SDLSetup(int screenWidth, int screenHeight);
    ~SDLSetup();
    SDL_Renderer* getRenderer();
    bool processEvents(int &goalX, int &goalY, int cellSize);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
};

#endif // SDL_SETUP_HPP
