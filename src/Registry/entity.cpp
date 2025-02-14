#include "entity.h"
#include <iostream>


float Fof(float value){
    if (value > 0) { return pow(value, 1/2); }
    return 0;
}
float Gof(float value){
    if (value > 0) { return pow(value, 2); }
    return 0;
}


float Decelerate(float value, float deltime){
    return Gof(Fof(value) - deltime);
}


Entity::Entity(Vector2 position, Vector2 velocity, float angle, SDL_FRect selection, float scale, float health, float animation){
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


bool Entity::Update(float deltime, Vector2 Mouse, SDL_MouseButtonFlags MouseStates, const bool * Keystates){


    if (Keystates[SDL_SCANCODE_W]){
        Velocity = (Position+Vector2(TextRect.w/2,TextRect.h/2)).Point(Mouse).Normalize() * 100;
    }
    else if (Keystates[SDL_SCANCODE_S]){
        Velocity = Decelerate(Velocity.Magnitude()-1, deltime * 1000);
    }
    else{
        Velocity = Velocity.Normalize() * Decelerate(Velocity.Magnitude(), deltime);
    }

    ((Position+Vector2(TextRect.w/2,TextRect.h/2)).Point(Mouse).Normalize().y);
    (Velocity.Normalize().x*((Position+Vector2(TextRect.w/2,TextRect.h/2)).Point(Mouse).Normalize().x))+(Velocity.Normalize().y*((Position+Vector2(TextRect.w/2,TextRect.h/2)).Point(Mouse).Normalize().y));


    Position += Velocity * deltime;
    Animation = fmod((Animation * (Velocity.Normalize().x*((Position+Vector2(TextRect.w/2,TextRect.h/2)).Point(Mouse).Normalize().x))+(Velocity.Normalize().y*((Position+Vector2(TextRect.w/2,TextRect.h/2)).Point(Mouse).Normalize().y)))+ (Velocity.Magnitude() * AnimStrength * Scale * Selection.h / Selection.w * deltime), TextureSize.y);
    Selection.y = (int)(abs(Animation)/Selection.h)*Selection.h;


    TextRect.x = Position.x;
    TextRect.y = Position.y;
    Center.x = (TextRect.w/2);
    Center.y = (TextRect.h/2);
    Angle = (Position+Vector2(TextRect.w/2,TextRect.h/2)).Point(Mouse).Rotation()/M_PI*180;
    return true;
}


bool Entity::Render(SDL_Renderer * renderer){
    SDL_RenderTextureRotated(renderer, Texture, &Selection, &TextRect, (double)Angle, &Center, SDL_FLIP_NONE);
    return true;
}
