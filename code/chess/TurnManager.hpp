#pragma once

#include "chess/Player.hpp"

class TurnManager {
public:
    void SetCurrentTurnToPlayerOne();
    void NextTurn();
    Player& GetActivePlayer();
    Player& GetOpponentPlayer();

private:
    Player player_one_ {"Black", EPlayerType::ONE};
    Player player_two_ {"Gray", EPlayerType::TWO};
    EPlayerType current_turn_ {EPlayerType::ONE};

    bool IsPlayerOneTurn() const;
};
