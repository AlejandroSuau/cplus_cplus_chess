#include "core/SDLInitializer.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>

SDLInitializer::SDLInitializer() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to init SDL: %s", SDL_GetError());
        throw std::runtime_error("Failed to init SDL");
    }
}
    
SDLInitializer::~SDLInitializer() {
    SDL_Quit();
}
