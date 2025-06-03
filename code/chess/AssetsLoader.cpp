#include "chess/AssetsLoader.hpp"

const std::string AssetsLoader::kPlayerOnePiecesId = "Player-One-Pieces";
const std::string AssetsLoader::kPlayerTwoPiecesId = "Player-Two-Pieces";
const std::string AssetsLoader::kBoardId = "Board-Perspective";

const std::unordered_map<EPieceType, SDL_Rect> AssetsLoader::kPiecesRects {
    {EPieceType::PAWN,   SDL_Rect{1, 32 - 16, 14, 16}},              // 14x16
    {EPieceType::KNIGHT, SDL_Rect{1 + 1*2 + 1*14, 32 - 20, 14, 20}}, // 14x20
    {EPieceType::ROOK,   SDL_Rect{1 + 2*2 + 2*14, 32 - 19, 14, 19}}, // 14x19
    {EPieceType::BISHOP, SDL_Rect{1 + 3*2 + 3*14, 32 - 21, 14, 21}}, // 14x21
    {EPieceType::QUEEN,  SDL_Rect{1 + 4*2 + 4*14, 32 - 24, 14, 24}}, // 14x24
    {EPieceType::KING,   SDL_Rect{1 + 5*2 + 5*14, 32 - 26, 14, 26}}, // 14x26
};

AssetsLoader::AssetsLoader(TextureManager& texture_manager) 
    : texture_manager_(texture_manager) {
    LoadAssets(); 
}
    
void AssetsLoader::LoadAssets() {
    texture_manager_.LoadTexture(
        "assets/images/chess/BlackPieces-Sheet.png", kPlayerOnePiecesId);
    texture_manager_.LoadTexture(
        "assets/images/chess/WhitePieces-Sheet.png", kPlayerTwoPiecesId);
    texture_manager_.LoadTexture(
        "assets/images/chess/Board-Perspective.png", kBoardId);
}

SDL_Texture* AssetsLoader::GetTexture(const std::string& id) {
    return texture_manager_.GetTexture(id);
}

const SDL_Rect& AssetsLoader::GetPieceRect(EPieceType type) const {
    auto piece_rect_it = kPiecesRects.find(type);
    assert(piece_rect_it != kPiecesRects.end() && "PieceType rect not defined");
    return piece_rect_it->second;
}

SDL_FRect AssetsLoader::GetCellRect(ColRow col_row) {
    return {
        kBoardOffset.x + col_row.x * kBoardTileSize.x,
        kBoardOffset.y + col_row.y * kBoardTileSize.y,
        kBoardTileSize.x,
        kBoardTileSize.y};
}
