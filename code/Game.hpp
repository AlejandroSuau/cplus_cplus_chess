#pragma once

#include <SDL2/SDL.h>

#include "core/SDLInitializer.hpp"
#include "core/SDLImageInitializer.hpp"
#include "core/SDLTTFInitializer.hpp"
#include "core/SDLMixerInitializer.hpp"

#include "utils/Renderer.hpp"
#include "utils/TextureManager.hpp"
#include "utils/TextManager.hpp"
#include "utils/bar/BarComponent.hpp"
#include "utils/bar/BarRenderer.hpp"
#include "utils/bar/BarLogic.hpp"
#include "utils/GameTimer.hpp"

#include "chess/ChessGame.hpp"

#include <memory>

class Game {
public:
    Game();
    
    void Run();
    void Shutdown();

private:
    // SDL Initializers
    std::unique_ptr<SDLInitializer> sdl_;
    std::unique_ptr<SDLImageInitializer> sdl_image_;
    std::unique_ptr<SDLTTFInitializer> sdl_ttf_;
    std::unique_ptr<SDLMixerInitializer> sdl_mixer_;

    // SDL window & render
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window_;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdl_renderer_;
    bool is_running_;

    Renderer renderer_;
    TextureManager texture_manager_;
    TextManager text_manager_;

    // Chess
    ChessGame chess_game_{text_manager_, texture_manager_};

    void Init();

    void Update(float dt);
    void Render();
    void HandleEvents();
};
