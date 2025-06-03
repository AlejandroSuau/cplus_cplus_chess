#pragma once

#include "chess/Definitions.hpp"

#include <string>

class Piece; 

class Cell {
public:
    Cell() = default;
    Cell(std::size_t index, ColRow col_row);
    
    const Piece* GetPiece() const;
    Piece* GetPiece();
    const ColRow GetColRow() const;

    void SetIndex(std::size_t index);
    void SetColRow(ColRow col_row);
    void SetPiece(Piece* piece);
    
    std::string Str() const;

private:
    std::size_t index_{};
    ColRow col_row_{};
    Piece* piece_{nullptr};
};