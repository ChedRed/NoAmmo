#pragma once
#include "../Vector2.h"
#include "registry.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <string>
#include <iostream>


class Entity{
    public:
    Entity(Vector2 position, Vector2 velocity, float angle, SDL_FRect selection, float scale, float health, float animation);
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


inline Entity::Entity(Vector2 position, Vector2 velocity, float angle, SDL_FRect selection, float scale, float health, float animation){
    Health = health;
    Angle = angle;
    Scale = scale;
    Position = position;
    Velocity = velocity;
    Selection = selection;
    AnimStrength = animation;
    TextRect.w = Selection.w * Scale;
    TextRect.h = Selection.h * Scale;
    TextRect.x = Position.x;
    TextRect.y = Position.y;
    UUID = SDL_randf();
}


inline bool Entity::Update(float deltime, Vector2 Mouse, SDL_MouseButtonFlags MouseStates, const bool * Keystates){


    if (Keystates[SDL_SCANCODE_W]){
        Velocity += Position.Point(Mouse);
        Velocity *= .8;
    }


    Position += Velocity * deltime;
    Animation += Velocity.Magnitude() * AnimStrength * deltime;
    Selection.y = fmod(Selection.y + Velocity.Magnitude(), TextureSize.y);


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
