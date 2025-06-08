#include "chess/ChessRules.hpp"

#include <optional>
#include <algorithm>

ChessRules::ChessRules(
        Board& board,
        const MovementFactory& movement_factory,
        const PieceManager& piece_manager)
    : board_(board)
    , movement_factory_(movement_factory)
    , piece_manager_(piece_manager) {}

Movements ChessRules::GetLegalMoves(Piece& piece) const {
    Movements legal_moves;
    for (const auto& move : movement_factory_.GetMovements(piece)) {
        if (WouldBeInCheckAfterMove(piece, move)) continue;
        
        legal_moves.push_back(move);
    }
    return legal_moves;
}

bool ChessRules::IsMoveLegal(Piece& piece, const ColRow& destination) const {
    auto legal_moves = GetLegalMoves(piece);
    return (std::find(legal_moves.cbegin(), legal_moves.cend(), destination) != legal_moves.end());
}

bool ChessRules::IsCheck(const Player& player) const {
    const auto king_pos_opt = piece_manager_.GetKing(player).GetPosition();
    if (!king_pos_opt) return false;
    const auto king_pos = king_pos_opt.value();

    for (const auto* piece : board_.GetCells()) {
        if (!piece || *piece->GetPlayer() == player) continue;

        const auto movements = movement_factory_.GetMovements(*piece);
        auto it = std::find_if(
            movements.cbegin(),
            movements.cend(),
            [&](const ColRow& move) { return (king_pos == move); });
        if (it != movements.cend()) return true;
    }

    return false;
}

bool ChessRules::IsCheckmate(const Player& player) const {
    return (IsCheck(player) && !HasAnyLegalMove(player));
}

bool ChessRules::IsStalemate(const Player& player) const {
    return (!IsCheck(player) && !HasAnyLegalMove(player));
}

bool ChessRules::HasAnyLegalMove(const Player& player) const {
    const auto& cells = board_.GetCells();
    auto it = std::find_if(cells.begin(), cells.end(), [&](Piece* p) {
        return (p && *p->GetPlayer() == player && !GetLegalMoves(*p).empty());
    });
    
    return (it != cells.end());
}

bool ChessRules::WouldBeInCheckAfterMove(Piece& piece, const ColRow& destination) const {
    // Piece + Colrow before movement.
    const auto colrow_from = *piece.GetPosition();

    // Piece + Colrow on the destination.
    auto* piece_on_destination = board_.GetPiece(destination);

    board_.MoveTo(piece, destination);
    bool is_check = IsCheck(*piece.GetPlayer());
    
    // Revert
    board_.MoveTo(piece, colrow_from);
    if (piece_on_destination) {
        board_.MoveTo(*piece_on_destination, destination);
    }

    return is_check;
}
