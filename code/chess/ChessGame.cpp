#include "chess/ChessGame.hpp"

#include "utils/Renderer.hpp"

ChessGame::ChessGame(TextManager& text_manager, TextureManager& texture_manager) 
    : text_manager_(text_manager)
    , texture_manager_(texture_manager)
    , assets_loader_(texture_manager)
    , movement_factory_(board_)
    , chess_rules_(board_, movement_factory_, piece_manager_)
    , controller_(board_, piece_manager_, turn_manager_, chess_rules_)
    , board_renderer_(texture_manager, text_manager, assets_loader_) {
    Init();
}

void ChessGame::Init() {
    font_big_ = text_manager_.LoadFont(Assets::kFontAtariPath, 5 * Config::kScalingFactor, Assets::kFontIdBig);
    font_small_ = text_manager_.LoadFont(Assets::kFontAtariPath, 3 * Config::kScalingFactor, Assets::kFontIdSmall);
    piece_manager_.Initialize(board_, turn_manager_);
}

void ChessGame::OnClick(float x, float y) {
    const auto col_row_opt = FromRealClickToBoardColRow(x, y);
    if (!col_row_opt) {
        SDL_Log(LogMessages::kClickOutOfBoard, x, y);
        return;
    }
    
    const auto col_row = col_row_opt.value();
    SDL_Log(LogMessages::kClickOnCell, col_row.x, col_row.y, turn_manager_.GetActivePlayer().Str().c_str());
    controller_.SelectOrMovePiece(col_row);
}

void ChessGame::OnKeyUp(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_l: BoardLoader::LoadFromJson(Assets::kJsonPath, board_, piece_manager_); break;
        case SDLK_r: controller_.ResetGame(); break;
    };
}

void ChessGame::Render(Renderer& renderer) {
    renderer.RenderText(
        *font_big_, "Chess Game", {255, 255, 255, 255}, Config::kScreenSize.x / 2, Config::kScreenSize.y * 0.05);
    renderer.RenderText(
        *font_small_, controller_.GetMessage(), {255, 255, 255, 255}, Config::kScreenSize.x / 2, Config::kScreenSize.y * 0.9);
    board_renderer_.Render(
        renderer, board_, controller_.GetHighlightedMoves(), controller_.GetSelectedPiece());
}
