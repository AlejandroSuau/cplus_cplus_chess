#include "Game.hpp"

#include <string>
#include <stdexcept>

namespace {
// Update
static constexpr Uint64 kTargetFPS = 60;
static constexpr Uint64 kFixedTimeStep = 1000 / kTargetFPS;
static constexpr Uint64 kFrameDelay = 1000 / kTargetFPS; // Frame delay in milliseconds
}

Game::Game()
    : sdl_(std::make_unique<SDLInitializer>())
    , sdl_image_(std::make_unique<SDLImageInitializer>())
    , sdl_ttf_(std::make_unique<SDLTTFInitializer>())
    , sdl_mixer_(std::make_unique<SDLMixerInitializer>())
    , window_(
        SDL_CreateWindow(
            "Tower Defense",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            static_cast<int>(ChessGame::kScreenSize.x),
            static_cast<int>(ChessGame::kScreenSize.y),
            0),
        SDL_DestroyWindow)
    , sdl_renderer_(
        SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer)
    , is_running_(false)
    , renderer_(*sdl_renderer_)
    , texture_manager_(*sdl_renderer_) {
    if (!window_ || !sdl_renderer_) {
        throw std::runtime_error(
            std::string("Error creating the game") + SDL_GetError());
    }
    
    SDL_SetRenderDrawBlendMode(sdl_renderer_.get(), SDL_BLENDMODE_BLEND);
}

void Game::Run() {
    Init();
    
    is_running_ = true;
    SDL_ShowWindow(window_.get());

    Uint64 previous_time = SDL_GetTicks64();
    Uint64 accumulated_time = 0;
    while (is_running_) {
        Uint64 current_time = SDL_GetTicks64();
        Uint64 frame_time = current_time - previous_time; // Delta time in milliseconds
        previous_time = current_time;
        accumulated_time += frame_time;

        HandleEvents();

        // Fixed Update Loop
        while (accumulated_time >= kFixedTimeStep) {
            Update(kFixedTimeStep / 1000.f); // Pass in seconds as a float
            accumulated_time -= kFixedTimeStep;
        }

        Render();

        Uint64 frame_end = SDL_GetTicks64();
        Uint64 frame_duration = frame_end - current_time;
        if (frame_duration < kFrameDelay) {
            SDL_Delay(static_cast<Uint32>(kFrameDelay - frame_duration));
        }
    }
}

void Game::Init() {}

void Game::Update(float dt) {}

void Game::Render() {
    auto* renderer = sdl_renderer_.get();
    SDL_RenderClear(renderer);

    chess_game_.Render(renderer_);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Game::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Shutdown();
            return;
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            chess_game_.OnClick(
                static_cast<float>(event.button.x),
                static_cast<float>(event.button.y));
        }

        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) {
            
        }
        
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r) {
        }
    }
}

void Game::Shutdown() {
    is_running_ = false;
}
