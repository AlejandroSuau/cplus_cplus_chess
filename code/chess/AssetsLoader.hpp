#pragma once

#include "utils/Vec2.hpp"
#include "utils/TextureManager.hpp"

#include "chess/Player.hpp"
#include "chess/Piece.hpp"

#include <unordered_map>
#include <assert.h>

#include <SDL2/SDL.h>
#include <SDL_image.h>

class AssetsLoader {
public:
    AssetsLoader(TextureManager& texture_manager);
    
    void LoadAssets();
    SDL_Texture* GetPlayerTexture(const Player& player);
    SDL_Texture* GetTexture(const std::string& id);
    const SDL_Rect& GetPieceRect(EPieceType type) const;
    static SDL_FRect GetCellRect(ColRow col_row);

private:
    static const std::unordered_map<EPieceType, SDL_Rect> kPiecesRects;

    TextureManager& texture_manager_;
};