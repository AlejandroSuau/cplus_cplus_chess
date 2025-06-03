#pragma once

#include "chess/Player.hpp"

class TurnManager {
public:
    void NextTurn();
    Player& GetActivePlayer();
    Player& GetOpponentPlayer();

private:
    Player player_one_ {"Player-One", EPlayerType::ONE};
    Player player_two_ {"Player-Two", EPlayerType::TWO};
    EPlayerType current_turn_ {EPlayerType::ONE};

    bool IsPlayerOneTurn() const;
};
