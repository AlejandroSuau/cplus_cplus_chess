#include "chess/PieceMover.hpp"

#include <assert.h>

PieceMover::PieceMover(Board& board) 
    : board_(board), movement_factory_(board), piece_(nullptr) {}

const Movements& PieceMover::ComputePieceMovements(Piece& piece, const Player& active_player) {
    piece_ = &piece;
    movements_ = movement_factory_.GetMovements(piece, active_player);
    return movements_;
}

bool PieceMover::DoesHaveMovements() const {
   return (movements_.size() > 0);
}

bool PieceMover::DoMovementsContain(const ColRow& col_row) const {
    return std::any_of(
        movements_.cbegin(),
        movements_.cend(),
        [&](const ColRow& cr) { return cr == col_row; });
}

const Movements& PieceMover::GetMovements() const {
    return movements_;
}

void PieceMover::MoveTo(const ColRow& col_row) {
    assert(piece_ && "Missing piece to move");
    
    piece_->IncreaseMovementsCount();
    board_.RemovePiece(*piece_);
    board_.AddPieceTo(*piece_, col_row);
}

void PieceMover::Reset() {
    piece_ = nullptr;
    movements_.clear();
}

const Piece* PieceMover::GetPiece() const {
    return piece_;
}
