//
//  sensor.cpp
//  RacingV2
//
//  Created by mac on 2023/1/16.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "sensor.hpp"

////////////////////////////////////////////////////

void Ray::update(float carX, float carY, float carAnglea)
{
    //  offset = 1.0;
     //reading.clear();
    colliding = false;
    this->start.x = carX;
    this->start.y = carY;
    this->end.x = carX-sin(this->rayAngle)*rayLength;
    this->end.y = carY-cos(this->rayAngle)*rayLength;
    
}
void Ray::render(SDL_Renderer *renderer)
{
    
    if(colliding)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        
        SDL_RenderDrawLine(renderer, this->start.x, this->start.y  ,this->end.x, this->end.y);
        
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer, this->start.x, this->start.y  ,this->end.x, this->end.y);
        
    }
}


////////////////////////////////////////////////////

////////////////////////////////////////////////////


std::vector<float> Sensor::getReadings()
{
    std::vector<float> readings;
    for(auto &r: rays)
    {
        readings.emplace_back(r.offset);
    }
    return readings;
}
std::vector<Vec2> Sensor::getRayEndPoints()
{
    std::vector<Vec2> endPoints;
    for(auto &r: rays)
    {
        endPoints.emplace_back(r.end);
    }
    return endPoints;
}
std::vector<Vec2> Sensor::getRayStartPoints()
{
    std::vector<Vec2> startPoints;
    for(auto &r: rays)
    {
        startPoints.emplace_back(r.start);
    }
    return startPoints;
}

void Sensor::update(float carX, float carY, float carAngle)
{
    for(float i = 0; i < this->rayCount;i++)
    {
        rays[i].rayAngle = LERP(this->raySpread/2,this->raySpread/2*-1 , i/(this->rayCount-1));
        rays[i].rayAngle-=carAngle*0.017453300000032111183;    //align rays with car angle
        rays[i].update(carX, carY, carAngle);
    }
}


void Sensor::render(SDL_Renderer *renderer)
{
    for(auto &r: rays)
    {
        r.render(renderer);
    }
    
}
