#include "chess/Piece.hpp"

Piece::Piece() : type_(EPieceType::INVALID) {}

Piece::Piece(EPieceType type) 
    : type_(type) {}

void Piece::Reset() {
    movements_count_ = 0;
    cell_ = nullptr;
    player_ = nullptr;
    type_ = EPieceType::INVALID;
}

void Piece::IncreaseMovementsCount() {
    ++movements_count_;
}

bool Piece::DidAlreadyMove() const {
    return (movements_count_ > 0);
}

bool Piece::DoesPlayerOwnThisPiece(const Player& player) const {
    return (*player_ == player);
}

bool Piece::IsKing() const {
    return (type_ == EPieceType::KING);
}

void Piece::SetPlayer(Player* player) {
    player_ = player;
}

void Piece::SetType(EPieceType type) {
    type_ = type;
}

void Piece::SetCell(Cell* cell) {
    cell_ = cell;
}

EPieceType Piece::GetType() const {
    return type_;
}

Cell* Piece::GetCell() {
    return cell_;
}

Player* Piece::GetPlayer() {
    return player_;
}

const Player* Piece::GetPlayer() const {
    return player_;
}

std::string Piece::Str() const {
    const auto type_it = PieceTypeString.find(type_);
    std::stringstream ss;
    ss << "{" << player_->Str() << " "
        << type_it->second << " - "
        << cell_->Str() << "\n}";
    return ss.str();
}
