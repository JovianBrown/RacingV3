//
//  opponent.cpp
//  RacingV2
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "opponent.hpp"
void Opponent::updateWayPoint()
{
    
    
    float wayPointAngle = 0;
    Vec2 wayPoint;
    wayPoint.x = path[wayPointIndex].x;
    wayPoint.y = path[wayPointIndex].y;
    wayPointAngle = path[wayPointIndex].angle;
    float distance = wayPoint.distance(position);
    
    
    if(wayPointAngle < getAngle())
    {
        left = true;
        right = false;
    }
    if(wayPointAngle > getAngle())
    {
        left = false;
        right = true;
    }
    if(distance > 0)
    {
        forward = true;
    }
    if(distance < 25)
    {
        std::cout<<"Incrementing waypoint"<<std::endl;
        wayPointIndex++;
    }
    if(wayPointIndex >= numOfPoints)
    {
        wayPointIndex = 0;
    }
}

void Opponent::renderWaypoint(SDL_Renderer *renderer)
{
    
    for(int i = 0; i < numOfPoints;i++)
    {
        
        Vec2 wayPoint;
        SDL_Rect waypointRect;
        wayPoint.x = path[i].x;
        wayPoint.y = path[i].y;
      //  wayPoint = camera->getTransformedPoint(wayPoint);
        waypointRect.x = wayPoint.x;
        waypointRect.y = wayPoint.y;
        
        waypointRect.w = 10;
        waypointRect.h = 10;
      //  Vec2 thisPos = camera->getTransformedPoint(position); //position of opponent transformed
        
        if(i == wayPointIndex)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &waypointRect);
            SDL_RenderDrawLine(renderer, wayPoint.x, wayPoint.y, position.x, position.y);
            
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            
            SDL_RenderDrawRect(renderer, &waypointRect);
        }
    }
    
    
}
