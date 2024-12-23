#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class Vector2{
float magnitude;
public:
Vector2(float X = 0, float Y = 0);
float Magnitude();
float x;
float y;
Vector2& operator+=(Vector2 B);
Vector2& operator-=(Vector2 B);
Vector2& operator*=(Vector2 B);
Vector2& operator/=(Vector2 B);
Vector2& operator*=(float B);
Vector2& operator/=(float B);
};

inline Vector2::Vector2(float X, float Y){
    x = X;
    y = Y;
}

inline float Vector2::Magnitude(){
    return std::sqrt((x*x)+(y*y));
}


// Vector x Vector operations
Vector2 operator+(Vector2 A, Vector2 B){
    return Vector2(A.x+B.x, A.y+B.y);
}

Vector2 operator-(Vector2 A, Vector2 B){
    return Vector2(A.x-B.x, A.y-B.y);
}

Vector2 operator*(Vector2 A, Vector2 B){
    return Vector2(A.x*B.x, A.y*B.y);
}

Vector2 operator/(Vector2 A, Vector2 B){
    return Vector2(A.x/B.x, A.y/B.y);
}

inline Vector2& Vector2::operator+=(Vector2 B){
    this->x += B.x;
    this->y += B.y;
    return *this;
}

inline Vector2& Vector2::operator-=(Vector2 B){
    this->x -= B.x;
    this->y -= B.y;
    return *this;
}

inline Vector2& Vector2::operator*=(Vector2 B){
    this->x *= B.x;
    this->y *= B.y;
    return *this;
}

inline Vector2& Vector2::operator/=(Vector2 B){
    this->x /= B.x;
    this->y /= B.y;
    return *this;
}


// Vector x Float operations
inline Vector2 operator*(Vector2 A, float B){
    return Vector2(A.x*B, A.y*B);
}

inline Vector2 operator/(Vector2 A, float B){
    return Vector2(A.x/B, A.y/B);
}

inline Vector2& Vector2::operator*=(float B){
    this->x *= B;
    this->y *= B;
    return *this;
}

inline Vector2& Vector2::operator/=(float B){
    this->x /= B;
    this->y /= B;
    return *this;
}
