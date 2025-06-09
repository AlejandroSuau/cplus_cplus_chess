#include "chess/GameController.hpp"

#include <SDL2/SDL_log.h>

#include <format>

GameController::GameController(
    Board& board,
    PieceManager& piece_manager,
    TurnManager& turn_manager,
    ChessRules& chess_rules)
    : board_(board)
    , piece_manager_(piece_manager)
    , turn_manager_(turn_manager)
    , chess_rules_(chess_rules)
    , did_game_end_(false)
    , selected_piece_(nullptr)
    , current_message_{std::format(LogMessages::kPlayerTurn, turn_manager_.GetActivePlayer().GetName())} {}
    
void GameController::SelectOrMovePiece(const ColRow& clicked_cell) {
    if (selected_piece_) {
        TryToMoveSelectedPiece(clicked_cell);
    } else {
        TryToSelectPiece(clicked_cell);
    }
}

void GameController::TryToMoveSelectedPiece(const ColRow& destination) {
    auto found_move_it = std::find(highlighted_moves_.cbegin(), highlighted_moves_.cend(), destination);
    const bool is_move_ok = (found_move_it != highlighted_moves_.cend());
    if (is_move_ok) {
        board_.MoveTo(*selected_piece_, destination);
        selected_piece_->IncreaseMovementsCount();
        turn_manager_.NextTurn();
        
        const auto& active_player = turn_manager_.GetActivePlayer();
        if (chess_rules_.IsCheckmate(active_player)) {
            current_message_ = LogMessages::kCheckmateWarning;
            did_game_end_ = true;
        }  else if (chess_rules_.IsStalemate(active_player)) {
            current_message_ = LogMessages::kStalemateWarning;
            did_game_end_ = true;
        } else if (chess_rules_.IsCheck(active_player)) {
            current_message_ = LogMessages::kCheckWarning;
        } else {
            current_message_ = std::format(LogMessages::kPlayerTurn, active_player.GetName());
        }
    }

    UnselectPiece();
}

bool GameController::DidGameEnd() const {
    return did_game_end_;
}

void GameController::ResetGame() {
    did_game_end_ = false;
    turn_manager_.SetCurrentTurnToPlayerOne();
    current_message_ = std::format(LogMessages::kPlayerTurn, turn_manager_.GetActivePlayer().GetName());
    board_.Clear();
    piece_manager_.ResetAllPieces();
    piece_manager_.Initialize(board_, turn_manager_);
}

void GameController::TryToSelectPiece(const ColRow& position) {
    auto* piece = board_.GetPiece(position);
    if (!piece || !piece->DoesPlayerOwnThisPiece(turn_manager_.GetActivePlayer())) return;

    SDL_Log(LogMessages::kPieceSelected, piece->Str().c_str());
    selected_piece_ = piece;
    highlighted_moves_ = chess_rules_.GetLegalMoves(*piece);
}

void GameController::UnselectPiece() {
    selected_piece_ = nullptr;
    highlighted_moves_.clear();
}

const Movements& GameController::GetHighlightedMoves() const {
    return highlighted_moves_;
}

Piece* GameController::GetSelectedPiece() const {
    return selected_piece_;
}

const std::string& GameController::GetMessage() const {
    return current_message_;
}
