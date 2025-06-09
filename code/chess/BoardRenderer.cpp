#include "chess/BoardRenderer.hpp"

#include "chess/Definitions.hpp"

#include "utils/RectOperations.hpp"

BoardRenderer::BoardRenderer(
    TextureManager& texture_manager,
    TextManager& text_manager,
    AssetsLoader& assets_loader)
    : texture_manager_(texture_manager)
    , text_manager_(text_manager)
    , assets_loader_(assets_loader) {}

void BoardRenderer::Render(
    Renderer& renderer,
    const Board& board,
    const Movements& highlights,
    Piece* selected_piece) {

    // Draw board background
    renderer.RenderTexture(
        assets_loader_.GetTexture(Assets::kBoardId),
        SDL_Rect{0, 0, Config::kBoardAssetSizeInt, Config::kBoardAssetSizeInt},
        SDL_FRect{Config::kBoardPosition.x, Config::kBoardPosition.y, Assets::kBoardAssetSize.x, Assets::kBoardAssetSize.y} * Config::kScalingFactor);

    // Draw highlight for selected piece
    if (selected_piece) {
        const auto pos = *selected_piece->GetPosition();
        auto cell_rect = AssetsLoader::GetCellRect(pos);
        cell_rect.x += Config::kBoardPosition.x;
        cell_rect.y += Config::kBoardPosition.y;
        renderer.SetRenderingColor({255, 255, 0, 150});
        renderer.RenderRectFilled(cell_rect * Config::kScalingFactor);
    }

    // Draw highlight moves for selected piece
    if (!highlights.empty()) {
        renderer.SetRenderingColor({0, 255, 0, 75});
        for (const auto& move : highlights) {
            auto cell_rect = AssetsLoader::GetCellRect(move);
            cell_rect.x += Config::kBoardPosition.x;
            cell_rect.y += Config::kBoardPosition.y;
            renderer.RenderRectFilled(cell_rect * Config::kScalingFactor);
        }
    }

    // Draw Pieces
    const auto& cells = board.GetCells();
    for (std::size_t i{}; i < cells.size(); ++i) {
        const auto* piece = cells[i];
        if (!piece) continue;

        const auto cell_col_row = board.FromIndexToColRow(i);
        auto cell_rect = AssetsLoader::GetCellRect(cell_col_row);
        cell_rect.x += Config::kBoardPosition.x;
        cell_rect.y += Config::kBoardPosition.y;
        const SDL_Rect& piece_rect_src = assets_loader_.GetPieceRect(piece->GetType());
        const SDL_FRect piece_rect_dst {
            (cell_rect.x + cell_rect.w * 0.5f  - static_cast<float>(piece_rect_src.w) / 2.f),
            (cell_rect.y + cell_rect.h * 0.75f - static_cast<float>(piece_rect_src.h)),
            static_cast<float>(piece_rect_src.w),
            static_cast<float>(piece_rect_src.h)};
        
        renderer.RenderTexture(
            assets_loader_.GetPlayerTexture(*piece->GetPlayer()),
            piece_rect_src,
            piece_rect_dst * Config::kScalingFactor);
    }
}
