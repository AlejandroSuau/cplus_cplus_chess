#pragma once

#include <string>
#include <unordered_map>

enum class EPlayerType {
    ONE, TWO
};

class Player {
public:
    Player(std::string name, EPlayerType type);

    bool IsPlayerOne() const;
    int GetDirection() const;

    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;
    
    std::string Str() const;

    EPlayerType GetType() const;
    std::string_view GetName() const;

private:
    std::string name_;
    EPlayerType type_;
    
    static const std::unordered_map<EPlayerType, std::string> kPlayerTypeString;
};
