#include "chess/Piece.hpp"

Piece::Piece() : type_(EPieceType::INVALID) {}

Piece::Piece(EPieceType type) 
    : type_(type) {}

void Piece::Reset() {
    movements_count_ = 0;
    position_ = std::nullopt;
    player_ = nullptr;
    type_ = EPieceType::INVALID;
}

void Piece::SetPosition(std::optional<ColRow> position) {
    position_ = position;
}

std::optional<ColRow> Piece::GetPosition() const {
    return position_;
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

EPieceType Piece::GetType() const {
    return type_;
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
        << type_it->second << " - ";
    if (position_) {
        ss << "[" << position_.value().x << "," << position_.value().y << "]" << "\n}";
    }
    return ss.str();
}
