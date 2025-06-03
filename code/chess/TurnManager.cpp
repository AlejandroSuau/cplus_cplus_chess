#include "chess/TurnManager.hpp"

void TurnManager::NextTurn() {
    current_turn_ = (IsPlayerOneTurn()) ? EPlayerType::TWO : EPlayerType::ONE;
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