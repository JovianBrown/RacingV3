//
//  vec2.hpp
//  RacingV3
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
struct Vec2
{
    float x;
    float y;
    Vec2();
    Vec2(const float& x, const float& y);
    Vec2& add(const Vec2& other);
    Vec2& subtract(const Vec2& other);
    Vec2& multiply(const Vec2& other);
    Vec2& divide(const Vec2& other);
    Vec2& scale(float scale);
    float dot(const Vec2& other);
    float distance(const Vec2& other);
    float magnitude();
    Vec2 normalize();
    Vec2 getCenter(SDL_Rect *rect);
    float magnitudeSq();
    
    friend std::ostream& operator<< (std::ostream& stream, const Vec2& vector);
    bool operator==(const Vec2& other);
    bool operator!=(const Vec2& other);
};

