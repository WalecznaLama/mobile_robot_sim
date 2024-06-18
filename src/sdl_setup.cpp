#include "sdl_setup.hpp"

SDLSetup::SDLSetup(int screenWidth, int screenHeight) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Robot Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

SDLSetup::~SDLSetup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* SDLSetup::getRenderer() {
    return renderer;
}

int SDLSetup::processEvents(int &xCell, int &yCell, int cellSize) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            return -1;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            xCell = y / cellSize; // NOTE x/y swapped
            yCell = x / cellSize;
            return 1;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_t) {  // Check if 't' key was pressed
                int x, y;
                SDL_GetMouseState(&x, &y);
                xCell = y / cellSize; // NOTE x/y swapped
                yCell = x / cellSize;
                return 2;  // Indicate that occupancy was toggled
            }
        }
    }
    return 0;
}
