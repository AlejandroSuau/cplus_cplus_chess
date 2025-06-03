#pragma once

#include "chess/Definitions.hpp"
#include "chess/Piece.hpp"
#include "chess/Board.hpp"
#include "chess/MovementFactory.hpp"

class PieceMover {
public:
    PieceMover(Board& board);

    const Movements& ComputePieceMovements(Piece& piece, const Player& active_player);
    bool DoesHaveMovements() const;
    bool DoMovementsContain(const ColRow& col_row) const;
    const Movements& GetMovements() const;
    void MoveTo(const ColRow& col_row);
    void Reset();

    const Piece* GetPiece() const;

private:
    Board& board_;
    MovementFactory movement_factory_;

    Piece* piece_;
    Movements movements_;
};
