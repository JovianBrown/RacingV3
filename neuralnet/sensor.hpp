//
//  sensor.hpp
//  RacingV2
//
//  Created by mac on 2023/1/16.
//  Copyright © 2023 Jovian. All rights reserved.
//


#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "utils.hpp"
//#include "../utils/vec2.hpp"
struct Ray
{
    Ray(float rayLength, float rayAngle, float carX, float carY)
    {
        this->rayLength = rayLength;
        this->rayAngle = rayAngle;
        this->start.x = carX;
        this->start.y = carY;
        this->end.x = carX-sin(this->rayAngle)*rayLength;
        this->end.x = carY-cos(this->rayAngle)*rayLength;
        
    }
    void update(float carX, float carY, float carAngle);
    void render(SDL_Renderer *renderer);
    Vec2 start;
    Vec2 end;
    std::vector<Vec2> readings;

    float rayLength;
    float rayAngle;
    float offset = 0.0;
    bool colliding = false;
    
};

class Sensor
{
public:
    Sensor(float rayCount, float rayLength, float carX, float carY)
    {
        this->rayCount = rayCount;
        this->rayLength = rayLength;
        this->raySpread = M_PI/1.6;  //0.785  45 degrees
        
        for(int i = 0; i < rayCount; i++)
        {
            float rayAngle = LERP(this->raySpread/2,this->raySpread/2*-1 , i/(this->rayCount-1));
            rays.push_back(Ray(rayLength, rayAngle, carX, carY));
        }
        
    }
    void update(float carX, float carY,float carAngle);
    void render(SDL_Renderer *renderer);
    std::vector<float> getReadings();
    std::vector<Ray> *getRays()
    {
        return &rays;
    }
    std::vector<Vec2> getRayEndPoints();
    std::vector<Vec2> getRayStartPoints();
    
private:
    float rayCount;
    float rayLength;
    float raySpread;
    std::vector<Ray> rays;
    
};

