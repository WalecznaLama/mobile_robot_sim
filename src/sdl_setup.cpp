#include "sdl_setup.hpp"

SDLSetup::SDLSetup(int screenWidth, int screenHeight, int cellSize) : _cellSize(cellSize) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to initialize SDL.");
    }

    window = SDL_CreateWindow("Robot Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("Failed to create window.");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Failed to create renderer.");
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

int SDLSetup::processEvents(int &xCell, int &yCell) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            return -1;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            xCell = y / _cellSize; // Convert screen to grid coordinates
            yCell = x / _cellSize;
            return 1; // Indicates a mouse button press event
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_t) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                xCell = y / _cellSize;
                yCell = x / _cellSize;
                return 2; // Indicates a 'toggle' key press
            }
        }
    }
    return 0; // No relevant event processed
}
