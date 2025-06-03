#include "core/SDLTTFInitializer.hpp"

#include <SDL2/SDL_ttf.h>

#include <stdexcept>

SDLTTFInitializer::SDLTTFInitializer() {
    if (TTF_Init() == -1) {
        SDL_Log("Failed to init SDL TTF: %s", SDL_GetError());
        throw std::runtime_error("Failed to init SDL TTF");
    }
}
    
SDLTTFInitializer::~SDLTTFInitializer() {
    TTF_Quit();
}