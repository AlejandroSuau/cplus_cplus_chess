#pragma once

#include "utils/Vec2.hpp"
#include "utils/Renderer.hpp"

#include <SDL2/SDL.h>

#include <cmath>

class BarRenderer {
public:
    BarRenderer(SDL_FRect background_rect) 
        : rect_background_(background_rect), rect_fill_(background_rect) {}
    
    void UpdateVisual(float progress) {
        rect_fill_.w = rect_background_.w * std::clamp(progress, 0.f, 1.f);
    }

    void Render(Renderer& renderer, SDL_Color bg_color, SDL_Color fill_color) {
        renderer.SetRenderingColor(bg_color);
        renderer.RenderRect(rect_background_);
        
        renderer.SetRenderingColor(fill_color);
        renderer.RenderRectFilled(rect_fill_);
    }

    void SetPosition(Vec2<float> pos) {
        rect_background_.x = pos.x;
        rect_background_.y = pos.y;
        rect_fill_.x = pos.x;
        rect_fill_.y = pos.y;
    }

private:
    SDL_FRect rect_background_;
    SDL_FRect rect_fill_;
};