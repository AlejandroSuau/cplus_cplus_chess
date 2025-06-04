#pragma once

#include "chess/TurnManager.hpp"
#include "chess/Board.hpp"

class PieceManager {
public:
    void Initialize(Board& board, TurnManager& turn_manager);
    
    const Piece& GetKing(const Player& player) const;

private:
    static constexpr std::size_t kPiecesPerPlayer = 16;
    static constexpr std::size_t kNumberOfPlayers = 2;
    // Traditional Chess order as default.
    std::array<Piece, kPiecesPerPlayer * kNumberOfPlayers > all_pieces_;

    /**
     * Traditional Chess Game Structure
     * 0-7  Pawn
     * 8-15 Rook-Knight-Bishop-Queen-King-Bishop-Knight-Rook
     */
    EPieceType GetPieceTypeByIndex(std::size_t index) const;
};
