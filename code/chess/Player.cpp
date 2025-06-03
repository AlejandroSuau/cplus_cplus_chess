#include "chess/Player.hpp"

#include <sstream>

const std::unordered_map<EPlayerType, std::string> Player::kPlayerTypeString {
    {EPlayerType::ONE, "Player One"},
    {EPlayerType::TWO, "Player Two"}
};

Player::Player(std::string name, EPlayerType type)
    : name_(std::move(name)), type_(type) {}

bool Player::IsPlayerOne() const {
    return (type_ == EPlayerType::ONE);
}

int Player::GetDirection() const {
    return (IsPlayerOne() ? 1 : -1);
}

std::string Player::Str() const {
    auto type_it = kPlayerTypeString.find(type_);
    std::stringstream ss;
    ss << type_it->second << " " << name_;
    return ss.str();
}

EPlayerType Player::GetType() const {
    return type_;
}

std::string_view Player::GetName() const {
    return name_;
}

bool Player::operator==(const Player& other) const {
    return (type_ == other.type_);
}

bool Player::operator!=(const Player& other) const {
    return !(*this == other);
}
