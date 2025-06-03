#include "chess/Board.hpp"

#include <assert.h>

Board::Board() {
    InitCells();
}

void Board::InitCells() {
    std::size_t index = 0;
    for (std::size_t row{}; row < kBoardSize; ++row) {
        for (std::size_t col{}; col < kBoardSize; ++col) {
            auto& cell = cells_[index];
            cell.SetIndex(index);
            cell.SetColRow(Vec2{col, row});
            ++index;
        }
    }
}

std::size_t Board::FromColRowToIndex(ColRow col_row) const {
    return (col_row.y * kBoardSize + col_row.x);
}

ColRow Board::FromIndexToColRow(std::size_t index) const {
    return {index % kBoardSize, index / kBoardSize};
}

bool Board::IsCellInsideBounds(ColRow col_row) const {
    return (col_row.x < kBoardSize && col_row.y < kBoardSize);
}

void Board::AddPieceTo(Piece& piece, const ColRow& col_row) {
    const auto cell_index = FromColRowToIndex(col_row);
    AddPieceTo(piece, cells_[cell_index]);
}

void Board::AddPieceTo(Piece& piece, Cell& cell) {
    piece.SetCell(&cell);
    cell.SetPiece(&piece);
}

void Board::RemovePiece(Piece& piece) {
    assert(piece.GetCell()->GetPiece() && "Trying to RemovePiece when not piece on that cell.");
    piece.GetCell()->SetPiece(nullptr);
    piece.SetCell(nullptr);
}

Cell& Board::GetCellByColRow(ColRow col_row) {
    const auto cell_index = FromColRowToIndex(col_row);
    return cells_[cell_index];
}

std::size_t Board::GetCellsSize() const {
    return cells_.size();
}

Cell& Board::GetCellByIndex(std::size_t i) {
    return cells_[i];
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
