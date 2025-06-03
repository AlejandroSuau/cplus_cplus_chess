#include "chess/MovementFactory.hpp"

#include <assert.h>

MovementFactory::MovementFactory(const Board& board) : board_(board) {}

Movements MovementFactory::GetMovements(Piece& piece, const Player& active_player) const {
    switch(piece.GetType()) {
        case EPieceType::PAWN:   return Pawn(piece, active_player);
        case EPieceType::ROOK:   return Rook(piece, active_player);
        case EPieceType::KNIGHT: return Knight(piece, active_player);
        case EPieceType::BISHOP: return Bishop(piece, active_player);
        case EPieceType::QUEEN:  return Queen(piece, active_player);
        case EPieceType::KING:   return King(piece, active_player);
        default:
            assert(false && "Not handled EPieceType!");
            return {};
    }
}

Movements MovementFactory::Pawn(Piece& piece, const Player& active_player) const {
    Movements movements;
    const int dir = active_player.GetDirection();
    const int max_move_units = (piece.DidAlreadyMove()) ? 1 : 2;

    // Forward
    const auto cr = piece.GetCell()->GetColRow();
    for (int step = 1; step <= max_move_units; ++step) {
        const ColRow forward {
            cr.x,
            static_cast<std::size_t>(static_cast<int>(cr.y) + step * dir)};
        
        if (!board_.IsCellInsideBounds((forward)) || board_.GetPiece(forward)) break;
        
        movements.push_back(forward);
    }

    // Diagonal
    static const std::array<int, 2> dx {-1, 1};
    for (auto i : dx) {
        int new_x = static_cast<int>(cr.x) + i;
        int new_y = static_cast<int>(cr.y) + dir;
        if (new_x < 0 || new_y < 0) continue;

        const ColRow diag {
            static_cast<std::size_t>(new_x),
            static_cast<std::size_t>(new_y)};
        if (!board_.IsCellInsideBounds(diag)) continue;

        auto* target = board_.GetPiece(diag);
        if (target && *target->GetPlayer() != active_player) {
            movements.push_back(diag);
        }
    }

    return movements;
}

Movements MovementFactory::Rook(Piece& piece, const Player& active_player) const {
    return ExploreDirections(piece.GetCell()->GetColRow(), kDirsRook, active_player);
}

Movements MovementFactory::Knight(Piece& piece, const Player& active_player) const {
    return ExploreDirections(piece.GetCell()->GetColRow(), kDirsKnight, active_player, true);
}

Movements MovementFactory::Bishop(Piece& piece, const Player& active_player) const {
    return ExploreDirections(piece.GetCell()->GetColRow(), kDirsBishop, active_player);
}

Movements MovementFactory::Queen(Piece& piece, const Player& active_player) const {
    return ExploreDirections(piece.GetCell()->GetColRow(), kDirsQueen, active_player);
}

Movements MovementFactory::King(Piece& piece, const Player& active_player) const {
    return ExploreDirections(piece.GetCell()->GetColRow(), kDirsQueen, active_player, true);
}

Movements MovementFactory::ExploreDirection(
    const ColRow& start, 
    const Vec2<int>& dir,
    const Player& player,
    bool is_doing_single_step) const {
    
    Movements result;
    int x = static_cast<int>(start.x) + dir.x;
    int y = static_cast<int>(start.y) + dir.y;
    while (x >= 0 && y >= 0 && 
            static_cast<std::size_t>(x) < board_.kBoardSize &&
            static_cast<std::size_t>(y) < board_.kBoardSize) {
        const ColRow target_col_row {
            static_cast<std::size_t>(x),
            static_cast<std::size_t>(y)};
        
        auto* cell_piece = board_.GetPiece(target_col_row);
        if (!cell_piece || *cell_piece->GetPlayer() != player) {
            result.push_back(target_col_row);
        }
        
        if (cell_piece || is_doing_single_step) break;

        x += dir.x;
        y += dir.y;
    }

    return result;
}
