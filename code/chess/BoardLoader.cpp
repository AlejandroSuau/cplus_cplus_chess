#include "chess/BoardLoader.hpp"

#include "chess/Piece.hpp"

#include <SDL2/SDL_log.h>

#include <fstream>

void BoardLoader::LoadFromJson(
    const std::string& path,
    Board& board,
    PieceManager& piece_manager) {

    std::ifstream file(path);
    if (!file.is_open()) {
        SDL_Log("Failed to open JSON file: %s", path.c_str());
        return;
    }

    nlohmann::json json_data;
    file >> json_data;

    auto& all_pieces = piece_manager.GetPieces();
    if (json_data["pieces"].size() > all_pieces.size()) {
        assert(false && "JSON pieces number is incorrect");
        return;
    }

    board.Clear();
    std::size_t i = 0;
    for (const auto& index_value : json_data["pieces"]) {
        if (!index_value.is_null()) {
            const auto index = index_value.get<std::size_t>();
            const auto colrow = board.FromIndexToColRow(index);
            auto& piece = all_pieces[i];
            board.MoveTo(piece, colrow);
        }
        ++i;
    }
}

