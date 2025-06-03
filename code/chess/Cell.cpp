#include "chess/Cell.hpp"

#include "chess/Piece.hpp"

#include <sstream>

Cell::Cell(std::size_t index, ColRow col_row)
    : index_(index), col_row_(col_row) {}
    
void Cell::SetIndex(std::size_t index) {
    index_ = index;
}

void Cell::SetColRow(ColRow col_row) {
    col_row_ = col_row;
}

const Piece* Cell::GetPiece() const {
    return piece_;
}

Piece* Cell::GetPiece() {
    return piece_;
}

const ColRow Cell::GetColRow() const {
    return col_row_;
}

void Cell::SetPiece(Piece* piece) {
    piece_ = piece;
}

std::string Cell::Str() const {
    std::stringstream ss;
    ss << "cell: [" << col_row_.x << "," << col_row_.y << "]";
    return ss.str();
}
