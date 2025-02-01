#pragma once
#include "../Vector2.h"
#include "registry.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <string>


class Entity{
    public:
    Entity(Vector2 position, Vector2 velocity, float angle, SDL_FRect selection, float health, float animation);
    bool Update(float deltime);
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
    SDL_Texture * Texture;
};


inline Entity::Entity(Vector2 position, Vector2 velocity, float angle, SDL_FRect selection, float health, float animation){
    Health = health;
    Angle = angle;
    Position = position;
    Velocity = velocity;
    Selection = selection;
    AnimStrength = animation;
    TextRect.w = Selection.x;
    TextRect.h = Selection.y;
    TextRect.x = Position.x;
    TextRect.y = Position.y;
    UUID = SDL_randf();
}


inline bool Entity::Update(float deltime){
    Position += Velocity;
    Animation += Velocity.Magnitude() * AnimStrength;
    Selection.y = float(int(Animation/Selection.h)) * Selection.h;

    TextRect.x = Position.x;
    TextRect.y = Position.y;
    Center.x = TextRect.x + (TextRect.w/2);
    Center.y = TextRect.y + (TextRect.h/2);
    return true;
}


inline bool Entity::Render(SDL_Renderer * renderer){
    SDL_RenderTextureRotated(renderer, Texture, &Selection, &TextRect, (double)Angle, &Center, SDL_FLIP_NONE);
    return true;
}
