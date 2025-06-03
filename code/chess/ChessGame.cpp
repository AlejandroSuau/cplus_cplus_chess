#include "chess/ChessGame.hpp"

#include "utils/Renderer.hpp"

SDL_FRect operator*(const SDL_FRect& rect, float scale) {
    return {rect.x * scale, rect.y * scale, rect.w * scale, rect.h * scale};
}

ChessGame::ChessGame(TextureManager& texture_manager) 
    : texture_manager_(texture_manager), assets_loader_(texture_manager_) { Init(); }

void ChessGame::Init() {
    piece_manager_.Initialize(board_, turn_manager_);
}

void ChessGame::OnClick(float x, float y) {
    // Translate from world.
    const auto col_row_opt = GetColRowFromClick(x, y);
    if (!col_row_opt) {
        SDL_Log("Clicked out of the board: %.0f, %.0f", x, y);
        return;
    }
    
    const auto col_row = col_row_opt.value();
    SDL_Log("Click detected on: [%zu, %zu]; Player: %s", col_row.x, col_row.y, turn_manager_.GetActivePlayer().Str().c_str());
    if (piece_mover_.DoesHaveMovements()) { // Something selected.
        if (piece_mover_.DoMovementsContain(col_row)) {
            assert(piece_mover_.GetPiece() && "There should be an active piece in MovementManager");
            piece_mover_.MoveTo(col_row);
            turn_manager_.NextTurn();
            SDL_Log("Swapped active player. Active player is now: %s", turn_manager_.GetActivePlayer().Str().c_str());
        }
        piece_mover_.Reset();
    } else {
        // Nothing previously selected.
        auto* piece = board_.GetPiece(col_row);
        if (piece && piece->DoesPlayerOwnThisPiece(turn_manager_.GetActivePlayer())) {
            SDL_Log("Piece selected!: %s", piece->Str().c_str());
            piece_mover_.ComputePieceMovements(*piece, turn_manager_.GetActivePlayer());
        }
    }
}

std::optional<ColRow> ChessGame::GetColRowFromClick(float x, float y) const {
    const auto real_x = x / kScalingFactor;
    const auto real_y = y / kScalingFactor;
    if (real_x < AssetsLoader::kBoardOffset.x || real_x > (AssetsLoader::kBoardOffset.x + AssetsLoader::kBoardDimensions.x) ||
        real_y < AssetsLoader::kBoardOffset.y || real_y > (AssetsLoader::kBoardOffset.y + AssetsLoader::kBoardDimensions.y)) {
        return std::nullopt;
    }

    const auto rel_board_x = real_x - AssetsLoader::kBoardOffset.x;
    const auto rel_board_y = real_y - AssetsLoader::kBoardOffset.y;
    return ColRow{
        static_cast<std::size_t>(rel_board_x / AssetsLoader::kBoardTileSize.x),
        static_cast<std::size_t>(rel_board_y / AssetsLoader::kBoardTileSize.y)};
}

void ChessGame::Render(Renderer& renderer) {
    renderer.RenderTexture(
        assets_loader_.GetTexture(AssetsLoader::kBoardId),
        SDL_Rect{0, 0, kBoardAssetSizeInt, kBoardAssetSizeInt},
        SDL_FRect{0.f, 0.f, AssetsLoader::kBoardAssetSize.x, AssetsLoader::kBoardAssetSize.y} * kScalingFactor);

    for (auto& c : board_.GetCells()) {
        const auto* piece = c.GetPiece();
        if (!piece) continue;
        
        const auto cell_rect = AssetsLoader::GetCellRect(c.GetColRow());
        const auto& asset_id = (piece->GetPlayer()->IsPlayerOne()) ? AssetsLoader::kPlayerOnePiecesId : AssetsLoader::kPlayerTwoPiecesId;
        const auto& piece_rect_src = assets_loader_.GetPieceRect(piece->GetType());
        const SDL_FRect piece_rect_dst {
            (cell_rect.x + cell_rect.w * 0.5f  - static_cast<float>(piece_rect_src.w) / 2.f),
            (cell_rect.y + cell_rect.h * 0.75f - static_cast<float>(piece_rect_src.h)),
            static_cast<float>(piece_rect_src.w),
            static_cast<float>(piece_rect_src.h)};
        renderer.RenderTexture(
            assets_loader_.GetTexture(asset_id),
            piece_rect_src,
            piece_rect_dst * kScalingFactor);
    }

    if (piece_mover_.DoesHaveMovements()) {
        renderer.SetRenderingColor({0, 255, 0, 35});
        const auto& active_possibilities = piece_mover_.GetMovements();
        for (const auto& p : active_possibilities) {
            const SDL_FRect cell_rect = AssetsLoader::GetCellRect(p) * kScalingFactor;
            renderer.RenderRectFilled(cell_rect);
        }
    }
}
