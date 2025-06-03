#pragma once

#include "chess/Player.hpp"
#include "chess/Definitions.hpp"

#include <sstream>
#include <unordered_map>
#include <string>
#include <optional>

enum class EPieceType {
    INVALID,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

const std::unordered_map<EPieceType, std::string> PieceTypeString {
    {EPieceType::INVALID, "Invalid"},
    {EPieceType::PAWN,    "Pawn"},
    {EPieceType::ROOK,    "Rook"},
    {EPieceType::KNIGHT,  "Knight"},
    {EPieceType::BISHOP,  "Bishop"},
    {EPieceType::QUEEN,   "Queen"},
    {EPieceType::KING,    "King"}
};

class Piece {
public:
    Piece();
    Piece(EPieceType type);

    void Reset();
    void IncreaseMovementsCount();
    bool DoesPlayerOwnThisPiece(const Player& player) const;
    bool DidAlreadyMove() const;
    std::string Str() const;

    bool IsKing() const;

    void SetType(EPieceType type);
    void SetPlayer(Player* player);
    void SetPosition(std::optional<ColRow> position);

    EPieceType GetType() const;
    std::optional<ColRow> GetPosition() const;
    Player* GetPlayer();
    const Player* GetPlayer() const;

private:
    EPieceType type_;
    std::optional<ColRow> position_{std::nullopt};
    Player* player_{nullptr};
    std::size_t movements_count_{0};
};