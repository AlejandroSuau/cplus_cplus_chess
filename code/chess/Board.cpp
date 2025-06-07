#include "chess/Board.hpp"

#include <assert.h>
#include <optional>

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

void Board::MoveTo(Piece& piece, const ColRow& destination) {
    auto previous_piece_pos = piece.GetPosition();
    if (previous_piece_pos) {
        const auto previous_cell_index_ = FromColRowToIndex(*previous_piece_pos);    
        cells_[previous_cell_index_] = nullptr;
    }

    const auto destination_index = FromColRowToIndex(destination);
    auto* piece_destination = cells_[destination_index];
    if (piece_destination) {
        piece_destination->SetPosition(std::nullopt);
    }

    cells_[destination_index] = &piece;
    piece.SetPosition(destination);
}

void Board::RemovePiece(Piece& piece) {
    const auto piece_pos = piece.GetPosition();
    assert(piece_pos && "Piece is not placed in the board");
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
