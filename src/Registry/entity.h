#pragma once
#include "../Vector2.h"
#include "registry.h"
#include <SDL3/SDL.h>
#include "../MoreMaths.h"
#include <string>


class Entity{
    public:
    Entity(Vector2 position, Vector2 velocity, float angle, SDL_FRect selection, float scale, float health, float animation = 1);
    bool Update(float deltime, Vector2 Mouse, SDL_MouseButtonFlags MouseStates, const bool * Keystates);
    bool Render(SDL_Renderer * renderer);
    float UUID;
    float Health;
    float DeathTime = -1;
    float Angle;
    float Animation;
    float AnimStrength;
    Vector2 Position;
    SDL_FPoint Center;
    Vector2 Velocity;
    SDL_FRect Selection;
    SDL_FRect TextRect;
    float Scale;
    SDL_Texture * Texture;
    Vector2 TextureSize;
};
