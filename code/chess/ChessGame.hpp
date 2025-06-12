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
#include "chess/BoardLoader.hpp"
#include "chess/AssetsLoader.hpp"
#include "chess/PieceManager.hpp"
#include "chess/TurnManager.hpp"
#include "chess/ChessRules.hpp"
#include "chess/GameController.hpp"
#include "chess/BoardRenderer.hpp"

#include "utils/Vec2.hpp"
#include "utils/TextureManager.hpp"
#include "utils/TextManager.hpp"

#include "utils/Renderer.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class ChessGame {
public:
    ChessGame(TextManager& text_manager, TextureManager& texture_manager);

    void Render(Renderer& renderer);
    void Init();
    void OnClick(float x, float y);
    void OnKeyUp(SDL_Keycode keycode);

private:
    TextManager& text_manager_;
    TextureManager& texture_manager_;

    AssetsLoader assets_loader_;
    Board board_;
    TurnManager turn_manager_;
    PieceManager piece_manager_;
    MovementFactory movement_factory_;
    ChessRules chess_rules_;

    GameController controller_;
    BoardRenderer board_renderer_;

    TTF_Font* font_small_;
    TTF_Font* font_big_;
};
