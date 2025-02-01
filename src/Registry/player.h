#pragma once
#include "../Vector2.h"
#include "entity.h"

class Player{
public:
Player(std::string username, Vector2 position);
std::string name;
Vector2 Position;
Vector2 Velocity;
Player(const Player&) = delete;
Player& operator=(const Player&) = delete;
};


inline Player::Player(std::string username, Vector2 position){
    name = username;
    Position = position;
}
