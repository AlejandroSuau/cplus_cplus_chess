#pragma once

#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <optional>

#include "chess/Player.hpp"
#include "chess/Piece.hpp"
#include "chess/Board.hpp"
#include "chess/PieceMover.hpp"
#include "chess/AssetsLoader.hpp"
#include "chess/PieceManager.hpp"
#include "chess/TurnManager.hpp"

#include "utils/Vec2.hpp"
#include "utils/TextureManager.hpp"

#include "utils/Renderer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class ChessGame {
public:
    static constexpr float kScalingFactor = 5.f;
    const int kBoardAssetSizeInt = static_cast<int>(AssetsLoader::kBoardAssetSize.x);
    static const std::size_t kScreenSize = static_cast<std::size_t>(kScalingFactor * AssetsLoader::kBoardAssetSize.x);

    ChessGame(TextureManager& texture_manager);

    void Render(Renderer& renderer);
    void Init();
    void OnClick(float x, float y);

private:
    TextureManager& texture_manager_;
    AssetsLoader assets_loader_;

    Board board_;
    PieceManager piece_manager_;
    PieceMover piece_mover_{board_};
    TurnManager turn_manager_;

    std::optional<ColRow> GetColRowFromClick(float x, float y) const;
};
