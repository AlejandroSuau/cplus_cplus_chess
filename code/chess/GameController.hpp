#pragma once

#include "chess/Board.hpp"
#include "chess/PieceManager.hpp"
#include "chess/TurnManager.hpp"
#include "chess/ChessRules.hpp"
#include "chess/Piece.hpp"
#include "chess/Definitions.hpp"

#include <string>

class GameController {
public:
    GameController(
        Board& board,
        PieceManager& piece_manager,
        TurnManager& turn_manager,
        ChessRules& chess_rules);
    
    void SelectOrMovePiece(const ColRow& clicked_cell);
    const Movements& GetHighlightedMoves() const;
    Piece* GetSelectedPiece() const;
    const std::string& GetMessage() const;
    bool DidGameEnd() const;
    void ResetGame();

private:
    Board& board_;
    PieceManager& piece_manager_;
    TurnManager& turn_manager_;
    ChessRules& chess_rules_;
    bool did_game_end_;

    Piece* selected_piece_;
    Movements highlighted_moves_;
    std::string current_message_;

    void TryToMoveSelectedPiece(const ColRow& destination);
    void TryToSelectPiece(const ColRow& position);
    void UnselectPiece();
};
