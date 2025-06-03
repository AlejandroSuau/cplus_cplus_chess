#pragma once

#include "utils/Vec2.hpp"
#include "utils/TextureManager.hpp"

#include "chess/Piece.hpp"

#include <unordered_map>
#include <assert.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class AssetsLoader {
public:
    static constexpr Vec2<float> kBoardAssetSize {142.f, 142.f};
    static constexpr Vec2<float> kBoardTileSize {16.f, 12.f};
    static constexpr Vec2<float> kBoardOffset {7.f, 20.f};
    static constexpr Vec2<float> kBoardDimensions {128.f, 96.f};

    static const std::string kPlayerOnePiecesId;
    static const std::string kPlayerTwoPiecesId;
    static const std::string kBoardId;
    
    AssetsLoader(TextureManager& texture_manager);
    
    void LoadAssets();
    SDL_Texture* GetTexture(const std::string& id);
    const SDL_Rect& GetPieceRect(EPieceType type) const;
    static SDL_FRect GetCellRect(ColRow col_row);

private:
    static const std::unordered_map<EPieceType, SDL_Rect> kPiecesRects;
    
    TextureManager& texture_manager_;
};