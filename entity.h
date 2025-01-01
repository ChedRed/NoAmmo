#pragma once
#include "Vector2.h"
#include "registry.h"
#include <string>

class Entity{
    Entity(Registry * registry, std::string id, std::string name);
    Vector2 Position;
    Vector2 Velocity;
    float health;
    private:
    Registry * Registre;
    std::string Name;
    std::string ID;
};

Entity::Entity(Registry * registry, std::string id, std::string name){
    Name = name;
    ID = id;
    Registre = registry;
    Register(registry, id, name);
}
