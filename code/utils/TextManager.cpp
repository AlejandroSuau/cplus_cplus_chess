#include "utils/TextManager.hpp"

TextManager::~TextManager() {
    ClearFonts();
}

TTF_Font* TextManager::LoadFont(const std::string& file_path, int font_size, std::string custom_id) {
    const std::string& font_id = custom_id.empty() ? file_path : custom_id;
    if (fonts_.count(font_id.c_str()) == 0) {
        TTF_Font* font = TTF_OpenFont(file_path.c_str(), font_size);
        if (!font) {
            SDL_Log("Failed to load font: %s", file_path.c_str());
            return nullptr;
        }
        fonts_.emplace(font_id.c_str(), font);
    }

    return fonts_[font_id.c_str()];
}

void TextManager::RemoveFont(const std::string& font_id) {
    auto it = fonts_.find(font_id.c_str());
    if (it == fonts_.end()) {
        SDL_Log("Trying to remove unexpected font: %s", font_id.c_str());
    } else {
        TTF_CloseFont(it->second);
        fonts_.erase(it);
    }
}

void TextManager::ClearFonts() {
    for (const auto& [font_id, font] : fonts_) {
        TTF_CloseFont(font);
    }
    fonts_.clear();
}