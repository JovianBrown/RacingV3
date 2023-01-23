//
//  vec2.cpp
//  RacingV2
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "vec2.hpp"
#include <cmath>
Vec2::Vec2()
{
    x = 0.0f;
    y = 0.0f;
    
}
float Vec2::
distance(const Vec2& other)
{
    float distance = abs(hypot(x,y)-hypot(other.x,other.y));
    // float bloog = sqrt(x,y);
    return distance;
}

Vec2::Vec2(const float& x, const float& y)
{
    this->x = x;
    this->y = y;
}

Vec2& Vec2::add(const Vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}
Vec2& Vec2::subtract(const Vec2& other)
{
    // Vec2 v(x-other.x,y-other.y);
    x -= other.x;
    y -= other.y;
    return *this;
    //  return v;
}
Vec2 Vec2::normalize()
{
    
    // Vec2 vec2((x/this->magnitude())*50,(y/this->magnitude())*50);
    Vec2 vec2((x/this->magnitude()),(y/this->magnitude()));
    return vec2;
}
Vec2 Vec2::getCenter(SDL_Rect *rect)
{
    return Vec2(rect->x+rect->w/2,rect->y+rect->h/2);
}
float Vec2::magnitude()
{
    float magnitude = hypot(x,y);
    return magnitude;
}
float Vec2::magnitudeSq()
{
    float magnitudeSq = x*x+y*y;
    return magnitudeSq;
}
Vec2& Vec2::scale(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}
float Vec2::dot(const Vec2& other)
{
    return x*other.x+y*other.y;
}

Vec2& Vec2::multiply(const Vec2& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vec2& Vec2::divide(const Vec2& other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}
bool Vec2::operator==(const Vec2& other)
{
    return x == other.x && y == other.y;
}
bool Vec2::operator!=(const Vec2& other)
{
    return !(*this == other);
}

std::ostream& operator<< (std::ostream& stream, const Vec2& vector)
{
    stream << "vec2: (" <<vector.x << ", "<<vector.y<<")";
    return stream;
}

