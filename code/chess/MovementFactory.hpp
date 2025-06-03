#pragma once

#include "chess/Definitions.hpp"

#include "chess/Player.hpp"
#include "chess/Piece.hpp"
#include "chess/Board.hpp"

class MovementFactory {
public:
    MovementFactory(const Board& board);
    Movements GetMovements(Piece& piece, const Player& active_player) const;

private:
    static constexpr std::array<Vec2<int>, 8> kDirsKnight {
        Vec2{-2, -1}, Vec2{-1, -2}, Vec2{1, -2}, Vec2{2, -1},
        Vec2{-2, 1}, Vec2{-1, 2}, Vec2{1, 2}, Vec2{2, 1}};
    static constexpr std::array<Vec2<int>, 4> kDirsRook {
        Vec2{0, -1}, Vec2{-1, 0}, Vec2{1, 0}, Vec2{0,  1}};
    static constexpr std::array<Vec2<int>, 4> kDirsBishop {
        Vec2{-1, -1}, Vec2{ 1, -1}, Vec2{-1,  1}, Vec2{ 1,  1}};
    static constexpr std::array<Vec2<int>, 8> kDirsQueen {
        Vec2{0, -1}, Vec2{-1, 0}, Vec2{1, 0}, Vec2{0,  1},
        Vec2{-1, -1}, Vec2{1, -1}, Vec2{-1, 1}, Vec2{1, 1},};
    
    const Board& board_;

    Movements Pawn(Piece& piece, const Player& active_player) const;
    Movements Rook(Piece& piece, const Player& active_player) const;
    Movements Knight(Piece& piece, const Player& active_playe) const;
    Movements Bishop(Piece& piece, const Player& active_playe) const;
    Movements Queen(Piece& piece, const Player& active_player) const;
    Movements King(Piece& piece, const Player& active_player) const;

    Movements ExploreDirection(
        const ColRow& start,
        const Vec2<int>& dir,
        const Player& player,
        bool is_doing_single_step) const;

    template<std::size_t N>
    Movements ExploreDirections(
        const ColRow& start, 
        const std::array<Vec2<int>, N>& directions,
        const Player& player,
        bool is_doing_single_step = false) const {
        
        Movements result;
        for (const auto& dir : directions) {
            auto partial = ExploreDirection(start, dir, player, is_doing_single_step);
            result.insert(result.end(), partial.begin(), partial.end());
        }
        return result;
    }
};
