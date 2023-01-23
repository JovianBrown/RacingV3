//
//  racetrack.cpp
//  Racingv3 new
//
//  Created by mac on 2023/1/2.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "racetrack.hpp"
void RaceTrack::update(Vehicle *car, std::vector<Opponent> &opponents, std::vector<AIVehicle> &aiVehicle)
{
    SDL_Rect carRect;
    carRect.x = car->getDest()->x;
    carRect.y = car->getDest()->y;
    carRect.w = car->getDest()->w;
    carRect.h = car->getDest()->h;
  
    for(auto &ai: aiVehicle)
    {
        SDL_Rect aiVehicleRect;
        aiVehicleRect.x = ai.getDest()->x;
        aiVehicleRect.y = ai.getDest()->y;
        aiVehicleRect.w = ai.getDest()->w;
        aiVehicleRect.h = ai.getDest()->h;
        for(auto &t: m_Tiles)
        {
            SDL_Rect currentTileRect;
            currentTileRect.x = t.tileLocation.x;
            currentTileRect.y = t.tileLocation.y;
            currentTileRect.w = t.tileLocation.w;
            currentTileRect.h = t.tileLocation.h;
            if(checkCollision(aiVehicleRect, currentTileRect))
            {
                ai.setCurrentTile(t.tileID);
                checkAllCollisions(&ai, *getTileByID(ai.getCurrentTile()));
                
            }
            for(auto &o: opponents)
            {
                SDL_Rect opponentRect = *o.getDest();
                if(checkCollision(opponentRect, currentTileRect))
                {
                    o.setCurrentTile(t.tileID);
                    if(t.m_TileType == 7) //grass
                    {
                        o.setDrag(0.03);
                        o.setMaxVelocity(1.0);
                    }
                    else
                    {
                        o.setDrag(0.01);
                    }
                }
            }
            
            if(checkCollision(carRect, currentTileRect))
            {
                car->setCurrentTile(t.tileID);
                Tile tile = *getTileByID(car->getCurrentTile());
                if(tile.m_TileType == 7) //grass
                {
                    car->setDrag(0.03);
                    car->setMaxVelocity(1.0);
                }
                else
                {
                    car->setMaxVelocity(2.0);
                    car->setDrag(0.01);
                }
            }
        }
    }
}
void RaceTrack::checkAllCollisions(AIVehicle *aiVehicle, Tile &tile)
{
    SDL_Rect rectNorth;
    rectNorth.x = tile.tileLocation.x;
    rectNorth.y = tile.tileLocation.y-tile.tileLocation.h;
    rectNorth.w = tile.tileLocation.w;
    rectNorth.h = tile.tileLocation.h;
    SDL_Rect rectSouth;
    rectSouth.x = tile.tileLocation.x;
    rectSouth.y = tile.tileLocation.y+tile.tileLocation.h;
    rectSouth.w = tile.tileLocation.w;
    rectSouth.h = tile.tileLocation.h;
    SDL_Rect rectWest;
    rectWest.x = tile.tileLocation.x-tile.tileLocation.w;
    rectWest.y = tile.tileLocation.y;
    rectWest.w = tile.tileLocation.w;
    rectWest.h = tile.tileLocation.h;
    SDL_Rect rectEast;
    rectEast.x = tile.tileLocation.x+tile.tileLocation.w;
    rectEast.y = tile.tileLocation.y;
    rectEast.w = tile.tileLocation.w;
    rectEast.h = tile.tileLocation.h;

    Tile tileNorth = *getTileByLocation(rectNorth);
    Tile tileSouth = *getTileByLocation(rectSouth);
    Tile tileWest = *getTileByLocation(rectWest);
    Tile tileEast = *getTileByLocation(rectEast);
    
    std::vector<Tile> importantTiles;
    importantTiles.emplace_back(tileNorth);
    importantTiles.emplace_back(tileSouth);
    importantTiles.emplace_back(tileWest);
    importantTiles.emplace_back(tileEast);
    importantTiles.emplace_back(tile);

    for(auto &t: importantTiles)
    {        
        for(auto &r: *aiVehicle->getSensors()->getRays())
        {
            if(twoLinesIntersect(r.start.x, r.start.y, r.end.x, r.end.y, t.collisionA.x1, t.collisionA.y1, t.collisionA.x2, t.collisionA.y2))
            {
                r.colliding = true;
                Vec2 intersectionPoint = twoLinesIntersectPoint(r.start.x, r.start.y, r.end.x, r.end.y, t.collisionA.x1, t.collisionA.y1, t.collisionA.x2, t.collisionA.y2);
                float offsetPercent = 1-(twoLinesOffset(r.start.x, r.start.y, r.end.x, r.end.y, t.collisionA.x1, t.collisionA.y1, t.collisionA.x2, t.collisionA.y2))/1;
                r.offset = offsetPercent;
                r.end = intersectionPoint;
                
            }
            else if(twoLinesIntersect(r.start.x, r.start.y, r.end.x, r.end.y, t.collisionB.x1, t.collisionB.y1, t.collisionB.x2, t.collisionB.y2))
            {
                r.colliding = true;
                Vec2 intersectionPoint = twoLinesIntersectPoint(r.start.x, r.start.y, r.end.x, r.end.y, t.collisionB.x1, t.collisionB.y1, t.collisionB.x2, t.collisionB.y2);
                float offsetPercent = 1-(twoLinesOffset(r.start.x, r.start.y, r.end.x, r.end.y, t.collisionB.x1, t.collisionB.y1, t.collisionB.x2, t.collisionB.y2))/1;
                r.offset = offsetPercent;
                r.end = intersectionPoint;
            }
        }
    }
    if(tile.m_TileType == 8 || tile.m_TileType == 2 ||tile.m_TileType == 1 ||tile.m_TileType == 5)  //if they are vertical tiles
    {
         aiVehicle->setDrag(0.01);
    }
    else if(tile.m_TileType == 7) //grass
    {
        aiVehicle->setDrag(0.03);
        aiVehicle->setMaxVelocity(1.0);
    }
    else
    {
        aiVehicle->setDrag(0.01);
    }

}
Tile * RaceTrack::getStartTile()
{
    return startTile;
}
void RaceTrack::render(SDL_Renderer *renderer)
{
    //   int tilesRendered = 0;
    bool drawCollisions = true;
    
    for(auto &t: m_Tiles)
    {
        
        SDL_Rect rect; //tile rectangle
        rect = t.tileLocation;
    
        
        //    if(checkCollision(*camera->getCameraRect(), rect)) //checks whether or not to clip sprite
        {
            //      tilesRendered++;
            
            switch (t.m_TileType)
            {
                case 1:
                    SDL_RenderCopyEx(renderer,trackLatTexture,&t.source,&rect,0,NULL,SDL_FLIP_NONE);
                    break;
                case 2:
                    SDL_RenderCopyEx(renderer,trackVertTexture,&t.source,&rect,0,NULL,SDL_FLIP_NONE);
                    break;
                case 3:
                    SDL_RenderCopyEx(renderer,trackLRTexture,&t.source,&rect,0,NULL,SDL_FLIP_NONE);
                    break;
                case 4:
                    SDL_RenderCopyEx(renderer,trackLRTexture,&t.source,&rect,-90,NULL,SDL_FLIP_NONE);
                    break;
                case 5:
                    SDL_RenderCopyEx(renderer,trackLRTexture,&t.source,&rect,-180,NULL,SDL_FLIP_NONE);
                    break;
                case 6:
                    SDL_RenderCopyEx(renderer,trackLRTexture,&t.source,&rect,-270,NULL,SDL_FLIP_NONE);
                    break;
                case 7:
                    SDL_RenderCopyEx(renderer,grassTexture,&t.source,&rect,0,NULL,SDL_FLIP_NONE);
                    break;
                case 8:
                    SDL_RenderCopyEx(renderer,trackVertStart,&t.source,&rect,0,NULL,SDL_FLIP_NONE);
                    break;
                    
            }
        }
        if(drawCollisions)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, t.collisionA.x1, t.collisionA.y1, t.collisionA.x2, t.collisionA.y2);
            SDL_RenderDrawLine(renderer, t.collisionB.x1, t.collisionB.y1, t.collisionB.x2, t.collisionB.y2);
        }
    }
    //    std::cout<<"Tiles rendererd "<<tilesRendered<<std::endl;
    
}
Tile* RaceTrack::getTileByLocation(SDL_Rect rect)
{
    for(auto &t: m_Tiles)
    {
        if(t.tileLocation.x == rect.x && t.tileLocation.y == rect.y)
        {
            return &t;
        }
    }
    //    std::cout<<"Unable to locate tile by location"<<std::endl;
    Tile *t = new Tile();
    return t;
}
Tile* RaceTrack::getTileByID(int tileID)
{
    for(auto &t: m_Tiles)
    {
        if(t.tileID == tileID)
        {
            return &t;
        }
        
        
    }
    std::cout<<"Unable to locate tile by id"<<std::endl;
    Tile *t = new Tile();
    return t;
}
