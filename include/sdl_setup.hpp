#ifndef SDL_SETUP_HPP
#define SDL_SETUP_HPP

#include <SDL2/SDL.h>
#include <iostream>

class SDLSetup {
public:
    SDLSetup(int screenWidth, int screenHeight);
    ~SDLSetup();
    SDL_Renderer* getRenderer();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // SDL_SETUP_HPP
