#pragma once

#include "chess/MovementFactory.hpp"
#include "chess/PieceManager.hpp"
#include "chess/Board.hpp"
#include "chess/Player.hpp"
#include "chess/Piece.hpp"
#include "chess/Definitions.hpp"

class ChessRules {
public:
    ChessRules(
        Board& board,
        const MovementFactory& movement_factory,
        const PieceManager& piece_manager);

    Movements GetLegalMoves(Piece& piece) const;
    bool IsMoveLegal(Piece& piece, const ColRow& destination) const;
    bool IsCheck(const Player& player) const;
    bool IsCheckmate(const Player& player) const;
    bool IsStalemate(const Player& player) const;

private:
    Board& board_;
    const MovementFactory& movement_factory_;
    const PieceManager& piece_manager_;
    
    bool WouldBeInCheckAfterMove(Piece& piece, const ColRow& destination) const;
    bool HasAnyLegalMove(const Player& player) const;
};
