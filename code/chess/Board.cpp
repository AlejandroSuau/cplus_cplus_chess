#include "chess/Board.hpp"

#include <assert.h>

Board::Board() {
    Clear();
}

void Board::Clear() {
    cells_.fill(nullptr);
}

std::size_t Board::FromColRowToIndex(ColRow col_row) const {
    return (col_row.y * kBoardSize + col_row.x);
}

ColRow Board::FromIndexToColRow(std::size_t index) const {
    return {index % kBoardSize, index / kBoardSize};
}

bool Board::IsInsideBounds(ColRow col_row) const {
    return (col_row.x < kBoardSize && col_row.y < kBoardSize);
}

void Board::AddPieceAt(Piece& piece, const ColRow& position) {
    const auto cell_index = FromColRowToIndex(position);
    cells_[cell_index] = &piece;
    piece.SetPosition(position);
}

void Board::RemovePiece(Piece& piece) {
    const auto piece_pos = piece.GetPosition();
    assert(piece_pos && "Piece hasn't a correct position");
    const auto cell_index = FromColRowToIndex(piece_pos.value());
    cells_[cell_index] = nullptr;
    piece.SetPosition(std::nullopt);
}

std::size_t Board::GetCellsSize() const {
    return kTotalCells;
}

Board::Cells& Board::GetCells() {
    return cells_;
}

const Board::Cells& Board::GetCells() const {
    return cells_;
}

Piece* Board::GetPiece(ColRow col_row) {
    return GetPieceImpl(*this, col_row);
}

const Piece* Board::GetPiece(ColRow col_row) const {
    return GetPieceImpl(*this, col_row);
}
