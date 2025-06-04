#pragma once

#include "chess/Definitions.hpp"

#include "chess/Player.hpp"
#include "chess/Piece.hpp"
#include "chess/Board.hpp"

class MovementFactory {
public:
    MovementFactory(const Board& board);
    Movements GetMovements(const Piece& piece) const;

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

    Movements Pawn(const Piece& piece) const;

    Movements ExploreDirection(
        const Piece& piece,
        const Vec2<int>& dir,
        bool is_doing_single_step) const;

    template<std::size_t N>
    Movements ExploreDirections(
        const Piece& piece, 
        const std::array<Vec2<int>, N>& directions,
        bool is_doing_single_step = false) const {
        
        Movements result;
        for (const auto& dir : directions) {
            auto partial = ExploreDirection(piece, dir, is_doing_single_step);
            result.insert(result.end(), partial.begin(), partial.end());
        }
        return result;
    }
};
