#pragma once

#include "chess/Cell.hpp"
#include "chess/Player.hpp"

#include <sstream>
#include <unordered_map>
#include <string>

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
    void SetCell(Cell* cell);

    EPieceType GetType() const;
    Cell* GetCell();
    Player* GetPlayer();
    const Player* GetPlayer() const;

private:
    EPieceType type_;
    Cell* cell_{nullptr};
    Player* player_{nullptr};
    std::size_t movements_count_{0};
};