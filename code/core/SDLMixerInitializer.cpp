#include "core/SDLMixerInitializer.hpp"

#include <SDL2/SDL.h>
#include <SDL_mixer.h>

#include <stdexcept>

SDLMixerInitializer::SDLMixerInitializer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
    }
}
    
SDLMixerInitializer::~SDLMixerInitializer() {
    Mix_CloseAudio();
}
