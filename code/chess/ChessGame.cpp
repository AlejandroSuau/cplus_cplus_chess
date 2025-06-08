#include "chess/ChessGame.hpp"

#include "utils/Renderer.hpp"

namespace {
    static const std::string kFontAtariPath {"assets/fonts/atari-full.ttf"};
    static const std::string kFontIdBig {"default-font-25"};
    static const std::string kFontIdSmall {"default-font-12"};
}

SDL_FRect operator*(const SDL_FRect& rect, float scale) {
    return {rect.x * scale, rect.y * scale, rect.w * scale, rect.h * scale};
}

ChessGame::ChessGame(TextManager& text_manager, TextureManager& texture_manager) 
    : text_manager_(text_manager)
    , texture_manager_(texture_manager)
    , assets_loader_(texture_manager_)
    , movement_factory_(board_)
    , chess_rules_(board_, movement_factory_, piece_manager_)
    , displaying_message_{.message = std::string(turn_manager_.GetActivePlayer().GetName()) + "'s Player Turn"} {
    Init();
}

void ChessGame::Init() {
    font_big_ = text_manager_.LoadFont(kFontAtariPath, 5 * kScalingFactor, kFontIdBig);
    font_small_ = text_manager_.LoadFont(kFontAtariPath, 2 * kScalingFactor, kFontIdSmall);

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
    if (selected_piece_) {
        if (std::find(highlighted_moves_.cbegin(), highlighted_moves_.cend(), col_row) != highlighted_moves_.cend()) {
            selected_piece_->IncreaseMovementsCount();
            board_.MoveTo(*selected_piece_, col_row);
            turn_manager_.NextTurn();
            SDL_Log("Swapped active player. Active player is now: %s", turn_manager_.GetActivePlayer().Str().c_str());
            displaying_message_.message = std::string(turn_manager_.GetActivePlayer().GetName()) + "'s Player Turn";
        }
        selected_piece_ = nullptr;
        highlighted_moves_.clear();

        if (chess_rules_.IsCheck(turn_manager_.GetActivePlayer())) {
            displaying_message_.message = "You're in Check!";
        }

    } else {
        auto* piece = board_.GetPiece(col_row);
        if (piece && piece->DoesPlayerOwnThisPiece(turn_manager_.GetActivePlayer())) {
            SDL_Log("Piece selected!: %s", piece->Str().c_str());
            selected_piece_ = piece;
            highlighted_moves_ = chess_rules_.GetLegalMoves(*piece);
        }
    }
}

std::optional<ColRow> ChessGame::GetColRowFromClick(float x, float y) const {
    const auto real_x = x / kScalingFactor;
    const auto real_y = y / kScalingFactor;
    if (real_x < (AssetsLoader::kBoardOffset.x + kBoardPosition.x) || real_x > (AssetsLoader::kBoardOffset.x + kBoardPosition.x + AssetsLoader::kBoardDimensions.x) ||
        real_y < (AssetsLoader::kBoardOffset.y + kBoardPosition.y) || real_y > (AssetsLoader::kBoardOffset.y + kBoardPosition.y + AssetsLoader::kBoardDimensions.y)) {
        return std::nullopt;
    }

    const auto rel_board_x = real_x - AssetsLoader::kBoardOffset.x - kBoardPosition.x;
    const auto rel_board_y = real_y - AssetsLoader::kBoardOffset.y - kBoardPosition.y;
    return ColRow{
        static_cast<std::size_t>(rel_board_x / AssetsLoader::kBoardTileSize.x),
        static_cast<std::size_t>(rel_board_y / AssetsLoader::kBoardTileSize.y)};
}

void ChessGame::Render(Renderer& renderer) {
    
    renderer.RenderText(
        *font_big_, "Chess Game", {255, 255, 255, 255}, kScreenSize.x / 2, kScreenSize.y * 0.05);

    renderer.RenderText(
        *font_small_, displaying_message_.message, displaying_message_.color, kScreenSize.x / 2, kScreenSize.y * 0.9);


    renderer.RenderTexture(
        assets_loader_.GetTexture(AssetsLoader::kBoardId),
        SDL_Rect{0, 0, kBoardAssetSizeInt, kBoardAssetSizeInt},
        SDL_FRect{kBoardPosition.x, kBoardPosition.y, AssetsLoader::kBoardAssetSize.x, AssetsLoader::kBoardAssetSize.y} * kScalingFactor);

    const auto& cells = board_.GetCells();
    for (std::size_t i{}; i < cells.size(); ++i) {
        const auto* piece = cells[i];
        if (!piece) continue;

        const auto cell_col_row = board_.FromIndexToColRow(i);
        auto cell_rect = AssetsLoader::GetCellRect(cell_col_row);
        cell_rect.x += kBoardPosition.x;
        cell_rect.y += kBoardPosition.y;
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

    if (!highlighted_moves_.empty()) {
        renderer.SetRenderingColor({0, 255, 0, 35});
        for (const auto& move : highlighted_moves_) {
            auto cell_rect = AssetsLoader::GetCellRect(move);
            cell_rect.x += kBoardPosition.x;
            cell_rect.y += kBoardPosition.y;
            renderer.RenderRectFilled(cell_rect * kScalingFactor);
        }
    }
}
