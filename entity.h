#pragma once
#include "Vector2.h"
#include "registry.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <string>


class RegEntity{
    public:
    RegEntity(Registry * registry, std::string id, std::string name);
    float Health;
    Vector2 Movement;
    std::string GetID();
    std::string GetName();
    private:
    Registry * Registre;
    std::string Name;
    std::string ID;
};


inline RegEntity::RegEntity(Registry * registry, std::string id, std::string name){
    Name = name;
    ID = id;
    Registre = registry;
    Register(registry, id, name);
}


class Entity{
    public:
    Entity(RegEntity entitype, std::string name);
    bool Update(float deltime);
    bool Render(SDL_Renderer * renderer);
    bool Exists;
    Vector2 Position;
    Vector2 Velocity;
    SDL_Texture * Texture;
    SDL_FRect TextRect;
    private:

};


inline Entity::Entity(RegEntity entitype, std::string name){
    // entitype.
}


inline bool Entity::Update(float deltime){
    return true;
}


inline bool Entity::Render(SDL_Renderer * renderer){
    // TextRect =
    SDL_RenderTexture(renderer, Texture, NULL, &TextRect);
    return true;
}
