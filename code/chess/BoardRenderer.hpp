#pragma once

#include "utils/TextureManager.hpp"
#include "utils/TextManager.hpp"
#include "utils/Renderer.hpp"

#include "chess/AssetsLoader.hpp"
#include "chess/Board.hpp"
#include "chess/Piece.hpp"

class BoardRenderer {
public:
    BoardRenderer(
        TextureManager& texture_manager,
        TextManager& text_manager,
        AssetsLoader& assets_loader);
    
    void Render(
        Renderer& renderer,
        const Board& board,
        const Movements& highlights,
        Piece* selected_piece);

private:
    TextureManager& texture_manager_;
    TextManager& text_manager_;
    AssetsLoader& assets_loader_;
};
