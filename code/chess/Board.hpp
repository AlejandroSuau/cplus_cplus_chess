#pragma once

#include "chess/Piece.hpp"
#include "chess/Definitions.hpp"

class Board {
public:
    static constexpr std::size_t kBoardSize = 8;
    static constexpr std::size_t kTotalCells = kBoardSize * kBoardSize;
    // Pointer to the piece if there are one, nullptr otherwise.
    using Cells = std::array<Piece*, kTotalCells>;

    Board();
    void Clear();

    std::size_t FromColRowToIndex(ColRow col_row) const;
    ColRow FromIndexToColRow(std::size_t index) const;
    bool IsInsideBounds(ColRow col_row) const;
    void MoveTo(Piece& piece, const ColRow& position);
    void RemovePiece(Piece& piece);
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
        return board.cells_[index];
    }
};