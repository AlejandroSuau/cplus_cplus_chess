#include "chess/PieceManager.hpp"

#include <assert.h>
#include <algorithm>

void PieceManager::Initialize(Board& board, TurnManager& turn_manager) {
    // Player One Pieces.
    for (std::size_t i{}; i < kPiecesPerPlayer; ++i) {
        auto& piece = all_pieces_[i];
        piece.SetPlayer(&turn_manager.GetActivePlayer());
        piece.SetType(GetPieceTypeByIndex(kPiecesPerPlayer - i - 1));
        board.AddPieceTo(piece, board.GetCellByIndex(i));
    }

    // Player Two Pieces.
    std::size_t piece_index = kPiecesPerPlayer;
    const auto cells_size = board.GetCellsSize();
    const std::size_t player_two_starting_index =  cells_size - kPiecesPerPlayer;
    for (std::size_t cell_index{player_two_starting_index}; cell_index < cells_size; ++cell_index) {
        auto& piece = all_pieces_[piece_index];
        piece.SetPlayer(&turn_manager.GetOpponentPlayer());
        piece.SetType(GetPieceTypeByIndex(piece_index % kPiecesPerPlayer));
        board.AddPieceTo(piece, board.GetCellByIndex(cell_index));
        ++piece_index;
    }
}

Piece& PieceManager::GetKing(const Player& player) {
    auto it = std::find_if(
        all_pieces_.begin(),
        all_pieces_.end(), [&](const Piece& piece) {
            return (*piece.GetPlayer() == player && piece.IsKing());
        });
    assert(it != all_pieces_.end() && "King not found");
    return *it;
}

EPieceType PieceManager::GetPieceTypeByIndex(std::size_t index) const {
    if (index < 8) return EPieceType::PAWN;
    switch(index) {
        case 8:  return EPieceType::ROOK;
        case 9:  return EPieceType::KNIGHT;
        case 10: return EPieceType::BISHOP;
        case 11: return EPieceType::QUEEN;
        case 12: return EPieceType::KING;
        case 13: return EPieceType::BISHOP;
        case 14: return EPieceType::KNIGHT;
        case 15: return EPieceType::ROOK;
        default:
            assert(false && "Invalid index");
            return EPieceType::INVALID;
    }
}
