#include "chess/TurnManager.hpp"

#include "chess/Definitions.hpp"

#include <SDL2/SDL_log.h>

void TurnManager::SetCurrentTurnToPlayerOne() {
    current_turn_ = EPlayerType::ONE;
}

void TurnManager::NextTurn() {
    current_turn_ = (IsPlayerOneTurn()) ? EPlayerType::TWO : EPlayerType::ONE;
    SDL_Log(LogMessages::kNextTurn, GetActivePlayer().Str().c_str());
}

Player& TurnManager::GetActivePlayer() {
    return (IsPlayerOneTurn()) ? player_one_ : player_two_; 
}

Player& TurnManager::GetOpponentPlayer() {
    return (IsPlayerOneTurn()) ? player_two_ : player_one_;
}

bool TurnManager::IsPlayerOneTurn() const {
    return (current_turn_ == EPlayerType::ONE);
}