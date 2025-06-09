#pragma once

#include "utils/Vec2.hpp"

#include <vector>
#include <string>
#include <optional>

using ColRow = Vec2<std::size_t>;
using Movements = std::vector<ColRow>;

// ASSETS
namespace Assets {
static const std::string kFontAtariPath {"assets/fonts/atari-full.ttf"};
static const std::string kFontIdBig {"default-font-big"};
static const std::string kFontIdSmall {"default-font-small"};
static const std::string kJsonPath {"assets/json/board_pieces.json"};

static const std::string kBlackPiecesPath {"assets/images/chess/BlackPieces-Sheet.png"};
static const std::string kWhitePiecesPath {"assets/images/chess/WhitePieces-Sheet.png"};
static const std::string kBoardPath {"assets/images/chess/Board-Perspective.png"};

static const std::string kPlayerOnePiecesId = "Player-One-Pieces";
static const std::string kPlayerTwoPiecesId = "Player-Two-Pieces";
static const std::string kBoardId = "Board-Perspective";

static constexpr Vec2<float> kBoardAssetSize {142.f, 142.f};
static constexpr Vec2<float> kBoardTileSize {16.f, 12.f};
static constexpr Vec2<float> kBoardOffset {7.f, 20.f};
static constexpr Vec2<float> kBoardDimensions {128.f, 96.f};
}

// CONFIG
namespace Config {
static constexpr float kScalingFactor = 5.f;

static constexpr Vec2<float> kScreenOffset {30.f, 20.f};
static constexpr Vec2<float> kBoardPosition {
    kScreenOffset.x - kScreenOffset.x / 2.f,
    kScreenOffset.y - kScreenOffset.y / 2.f
};

static constexpr Vec2<std::size_t> kScreenSize {
    static_cast<std::size_t>(kScalingFactor * (Assets::kBoardAssetSize.x + kScreenOffset.x)),
    static_cast<std::size_t>(kScalingFactor * (Assets::kBoardAssetSize.y + kScreenOffset.y))
};

const int kBoardAssetSizeInt = static_cast<int>(Assets::kBoardAssetSize.x);
}

// LOGMESSAGES
namespace LogMessages {
static constexpr const char* kClickOnCell = "Clicked cell [%zu, %zu] by %s";
static constexpr const char* kClickOutOfBoard = "Clicked out of the board -> coords {%.0f, %0.f}";
static constexpr const char* kNextTurn = "Next turn. Active player is now: %s";
static constexpr const char* kPieceSelected = "Selected piece: %s";

// Screen Message
static constexpr const char* kPlayerTurn = "{}'s Player Turn";
static constexpr const char* kCheckWarning = "You're in check! Move!";
static constexpr const char* kCheckmateWarning = "You're in checkmate! GG. Press 'R' to reset";
}

constexpr std::optional<ColRow> FromRealClickToBoardColRow(float x, float y) {
    const auto real_x = x / Config::kScalingFactor;
    const auto real_y = y / Config::kScalingFactor;
    if (real_x < (Assets::kBoardOffset.x + Config::kBoardPosition.x) || real_x > (Assets::kBoardOffset.x + Config::kBoardPosition.x + Assets::kBoardDimensions.x) ||
        real_y < (Assets::kBoardOffset.y + Config::kBoardPosition.y) || real_y > (Assets::kBoardOffset.y + Config::kBoardPosition.y + Assets::kBoardDimensions.y)) {
        return std::nullopt;
    }

    const auto rel_board_x = real_x - Assets::kBoardOffset.x - Config::kBoardPosition.x;
    const auto rel_board_y = real_y - Assets::kBoardOffset.y - Config::kBoardPosition.y;
    return ColRow{
        static_cast<std::size_t>(rel_board_x / Assets::kBoardTileSize.x),
        static_cast<std::size_t>(rel_board_y / Assets::kBoardTileSize.y)};
}