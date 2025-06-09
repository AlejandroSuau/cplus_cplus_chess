#pragma once

#include "chess/Board.hpp"
#include "chess/PieceManager.hpp"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

class BoardLoader {
public:
    static void LoadFromJson(
        const std::string& path,
        Board& board,
        PieceManager& piece_manager);
};
