#pragma once

#include "chess/Piece.hpp"
#include "chess/Cell.hpp"
#include "chess/Definitions.hpp"

class Board {
public:
    static const std::size_t kBoardSize = 8;
    using Cells = std::array<Cell, kBoardSize * kBoardSize>;

    Board();
    void InitCells();

    std::size_t FromColRowToIndex(ColRow col_row) const;
    ColRow FromIndexToColRow(std::size_t index) const;
    bool IsCellInsideBounds(ColRow col_row) const;
    void AddPieceTo(Piece& piece, const ColRow& col_row);
    void AddPieceTo(Piece& piece, Cell& cell);
    void RemovePiece(Piece& piece);
    Cell& GetCellByColRow(ColRow col_row);
    Cell& GetCellByIndex(std::size_t i);
    const Piece* GetPiece(ColRow col_row) const;
    Piece* GetPiece(ColRow col_row);
    Cells& GetCells();
    const Cells& GetCells() const;
    std::size_t GetCellsSize() const;

private:
    Cells cells_;

    // This method allow us to avoid code duplication on GetCell method.
    // Qualifier (const) does not modify GetPiece implementation.
    template<typename BoardT>
    static auto GetPieceImpl(BoardT& board, ColRow col_row) {
        const auto index = board.FromColRowToIndex(col_row);
        return board.cells_[index].GetPiece();
    }
};