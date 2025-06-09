#pragma once

#include <SDL2/SDL_rect.h>

constexpr SDL_FRect operator*(const SDL_FRect& rect, float scale) {
    return {rect.x * scale, rect.y * scale, rect.w * scale, rect.h * scale};
}
