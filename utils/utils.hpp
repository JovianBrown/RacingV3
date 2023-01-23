
//
//  utils.hpp
//  RacingV3
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include "vec2.hpp"
inline float LERP(float A, float B, float T)
{
    return A+(B-A)*T;
}

inline void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);
    
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);
    
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
        
        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }
        
        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
inline bool checkCollision( SDL_Rect a, SDL_Rect b )  //check collision between two rectangles
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

inline float getHypotenuse(float a, float b)
{
    float aProd = a*a;
    float bProd = b*b;
    float abSum = aProd + bProd;
    float squareRT = sqrt(abSum);
    return squareRT;
    
}
inline float toRadians(float degrees)
{
    return degrees * (M_PI / 180.0f);
}
inline float twoLinesOffset(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    
    // calculate the distance to the intersection points
    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    
    /////////
    
    float tTop=(x4-x3)*(y1-y3)-(y4-y3)*(x1-x3);
    float bottom=(y4-y3)*(x2-x1)-(x4-x3)*(y2-y1);
    float t=tTop/bottom;
    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
    {
        
        // intersection point
        Vec2 intersectionPoint;
        intersectionPoint.x = x1 + (uA * (x2-x1));
        intersectionPoint.y = y1 + (uA * (y2-y1));;
        return t;
    }
    else
    {
        
        return 0.0;
    }
}

inline Vec2 twoLinesIntersectPoint(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    
    // calculate the distance to the intersection points
    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    
    /////////
    
    float tTop=(x4-x3)*(y1-y3)-(y4-y3)*(x1-x3);
    float bottom=(y4-y3)*(x2-x1)-(x4-x3)*(y2-y1);
    float t=tTop/bottom;
    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        
        // intersection point
        float intersectionX = x1 + (uA * (x2-x1));
        float intersectionY = y1 + (uA * (y2-y1));
        
        Vec2 intersectionPoint;
        intersectionPoint.x = intersectionX;
        intersectionPoint.y = intersectionY;
        
      //  float offsetT = t;
     //   std::cout<<"Offset T "<<offsetT<<std::endl;
     //   float xLERP = LERP(x1, x2, t);   need to get offset instead of intersectionPoint
     //   float yLERP = LERP(y1, y2, t);
        return intersectionPoint;
    }
    return Vec2();
}
inline std::vector<Vec2> lineAndRectIntersectPoint(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh)
{
  
  //  Vec2 leftIntersect = twoLinesIntersectPoint(x1,y1,x2,y2, rx,ry,rx, ry+rh);
  //  Vec2 rightIntersect = twoLinesIntersectPoint(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
  //  Vec2 topIntersect = twoLinesIntersectPoint(x1,y1,x2,y2, rx,ry, rx+rw,ry);
  //  Vec2 bottomIntersect = twoLinesIntersectPoint(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);
    std::vector<Vec2> intersects;
    std::vector<Vec2> intersectPoints;
    
    for(auto &v2: intersects)
    {
        if(v2.x || v2.y)
        {
            intersectPoints.emplace_back(v2);
        }
    }
    return intersectPoints;
}
inline bool twoLinesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    
    // calculate the distance to the intersection points
    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    
    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        
     
    
        return true;
    }
    return false;
}
struct line
{
    line()
    {
        
    }
    line(float x1, float y1, float x2, float y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;

    }
    float x1;   
    float y1;
    float x2;
    float y2;
};
#endif /* utils_hpp */
