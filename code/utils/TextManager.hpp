#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <unordered_map>
#include <string>

class TextManager final {
public:
    TextManager() = default;
    ~TextManager();

    TTF_Font* GetFont(const std::string& id);
    TTF_Font* LoadFont(const std::string& file_path, int font_size, const std::string& custom_id = "");
    void RemoveFont(const std::string& font_id);

private:
    TextManager(const TextManager&) noexcept = delete;
    TextManager(TextManager&&) noexcept = delete;
    TextManager& operator=(const TextManager&) noexcept = delete;
    TextManager& operator=(TextManager&&) noexcept = delete;

    std::unordered_map<std::string, TTF_Font*> fonts_;

    void ClearFonts();
};
