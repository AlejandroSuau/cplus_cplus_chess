#include "chess/MovementFactory.hpp"

#include <assert.h>

MovementFactory::MovementFactory(const Board& board) : board_(board) {}

Movements MovementFactory::GetMovements(const Piece& piece) const {
    assert(piece.GetPosition() && "Piece has a wrong position");
    assert(piece.GetPlayer() && "Piece has no player assigned");

    switch(piece.GetType()) {
        case EPieceType::PAWN:   return Pawn(piece);
        case EPieceType::ROOK:   return ExploreDirections(piece, kDirsRook);
        case EPieceType::KNIGHT: return ExploreDirections(piece, kDirsKnight, true);
        case EPieceType::BISHOP: return ExploreDirections(piece, kDirsBishop);
        case EPieceType::QUEEN:  return ExploreDirections(piece, kDirsQueen);
        case EPieceType::KING:   return ExploreDirections(piece, kDirsQueen, true);
        default:
            assert(false && "Not handled EPieceType!");
            return {};
    }
}

Movements MovementFactory::Pawn(const Piece& piece) const {
    Movements movements;
    const int dir = piece.GetPlayer()->GetDirection();
    const int max_move_units = (piece.DidAlreadyMove()) ? 1 : 2;
    const auto position = piece.GetPosition().value();

    // Forward
    for (int step = 1; step <= max_move_units; ++step) {
        const ColRow forward {
            position.x,
            static_cast<std::size_t>(static_cast<int>(position.y) + step * dir)};
        
        if (!board_.IsInsideBounds((forward)) || board_.GetPiece(forward)) break;
        
        movements.push_back(forward);
    }

    // Diagonal
    static const std::array<int, 2> dx {-1, 1};
    for (auto i : dx) {
        int new_x = static_cast<int>(position.x) + i;
        int new_y = static_cast<int>(position.y) + dir;
        if (new_x < 0 || new_y < 0) continue;

        const ColRow diag {
            static_cast<std::size_t>(new_x),
            static_cast<std::size_t>(new_y)};
        if (!board_.IsInsideBounds(diag)) continue;

        auto* target = board_.GetPiece(diag);
        if (target && *target->GetPlayer() != *piece.GetPlayer()) {
            movements.push_back(diag);
        }
    }

    return movements;
}

Movements MovementFactory::ExploreDirection(
    const Piece& piece,
    const Vec2<int>& dir,
    bool is_doing_single_step) const {
    
    const auto position = piece.GetPosition().value();
    Movements result;
    int x = static_cast<int>(position.x) + dir.x;
    int y = static_cast<int>(position.y) + dir.y;
    while (x >= 0 && y >= 0 && 
            static_cast<std::size_t>(x) < board_.kBoardSize &&
            static_cast<std::size_t>(y) < board_.kBoardSize) {
        const ColRow target_col_row {
            static_cast<std::size_t>(x),
            static_cast<std::size_t>(y)};
        
        auto* cell_piece = board_.GetPiece(target_col_row);
        if (!cell_piece || *cell_piece->GetPlayer() != *piece.GetPlayer()) {
            result.push_back(target_col_row);
        }
        
        if (cell_piece || is_doing_single_step) break;

        x += dir.x;
        y += dir.y;
    }

    return result;
}
