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
#include "chess/AssetsLoader.hpp"
#include "chess/PieceManager.hpp"
#include "chess/TurnManager.hpp"
#include "chess/ChessRules.hpp"

#include "utils/Vec2.hpp"
#include "utils/TextureManager.hpp"
#include "utils/TextManager.hpp"

#include "utils/Renderer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

struct ScreenDisplayingMessage {
    std::string message {"This is a default message"};
    SDL_Color color {255, 255, 255, 255};
};

class ChessGame {
public:
    static constexpr float kScalingFactor = 5.f;
    const int kBoardAssetSizeInt = static_cast<int>(AssetsLoader::kBoardAssetSize.x);
    static constexpr Vec2<float> kScreenOffset {30.f, 20.f};
    static constexpr Vec2<std::size_t> kScreenSize {
        static_cast<std::size_t>(kScalingFactor * (AssetsLoader::kBoardAssetSize.x + kScreenOffset.x)),
        static_cast<std::size_t>(kScalingFactor * (AssetsLoader::kBoardAssetSize.y + kScreenOffset.y))
    };

    static constexpr Vec2<float> kBoardPosition {
        kScreenOffset.x - kScreenOffset.x / 2.f,
        kScreenOffset.y - kScreenOffset.y / 2.f
    };

    ChessGame(TextManager& text_manager, TextureManager& texture_manager);

    void Render(Renderer& renderer);
    void Init();
    void OnClick(float x, float y);

private:
    TextManager& text_manager_;
    TextureManager& texture_manager_;
    AssetsLoader assets_loader_;

    Board board_;
    TurnManager turn_manager_;
    PieceManager piece_manager_;
    MovementFactory movement_factory_;
    ChessRules chess_rules_;
    ScreenDisplayingMessage displaying_message_;
    
    Piece* selected_piece_;
    Movements highlighted_moves_;

    TTF_Font* font_small_;
    TTF_Font* font_big_;

    std::optional<ColRow> GetColRowFromClick(float x, float y) const;
};
