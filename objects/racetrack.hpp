//
//  racetrack.hpp
//  RacingV3
//
//  Created by mac on 2023/1/18.
//  Copyright © 2023 Jovian. All rights reserved.
// new

#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include "SDL2/SDL.h"
#include "vehicle.hpp"
#include "opponent.hpp"
#include "aivehicle.hpp"
#include "../utils/utils.hpp"
#include "../utils/loadtrack.hpp"
#include <SDL2_image/SDL_image.h>

struct Tile
{
    Tile()
    {
        
    }
    Tile(float x, float y,int tileType, int tileID)
    {
        float tileWidth = 64;
        float tileHeight = 64;
        source.x = 0;
        source.y = 0;
        source.w = 192;
        source.h = 192;
        tileLocation.x = x;
        tileLocation.y = y;
        tileLocation.w = tileWidth;
        tileLocation.h = tileHeight;
        m_TileType = tileType;
        this->tileID = tileID;
      //  std::cout<<"Tile ID "<<tileID<<std::endl;
        if(m_TileType == 8 || m_TileType == 2) ///if track tile is verticle or the verticle start tile
        {
            ///collision line on left side
            
            collisionA.x1 = x;
            collisionA.y1 = y;
            collisionA.x2 = x;
            collisionA.y2 = y+tileHeight;
            ///collision line on right side
            
            collisionB.x1 = x+tileWidth;
            collisionB.y1 = y;
            collisionB.x2 = x+tileWidth;
            collisionB.y2 = y+tileHeight;
        }
        else if(m_TileType == 1 ) ///horizontal
        {
            ///collision line on top side
            
            collisionA.x1 = x;
            collisionA.y1 = y;
            collisionA.x2 = x+tileWidth;
            collisionA.y2 = y;
            ///collision line on bottom side
            collisionB.x1 = x;
            collisionB.y1 = y+tileHeight;
            collisionB.x2 = x+tileWidth;
            collisionB.y2 = y+tileHeight;
        }
        else if(m_TileType == 4 )
        {
            collisionA.x1 = x;
            collisionA.y1 = y;
            collisionA.x2 = x+tileWidth;
            collisionA.y2 = y+tileHeight;
        }
        else if(m_TileType == 5 )
        {
            collisionA.x1 = x;
            collisionA.y1 = y+tileHeight/1.1;
            collisionA.x2 = x+tileWidth/1.1;
            collisionA.y2 = y;
        }
        else if(m_TileType == 3 )
        {
            collisionA.x1 = x;
            collisionA.y1 = y+tileHeight/1.1;
            collisionA.x2 = x+tileWidth/1.1;
            collisionA.y2 = y;
        }
        else if(m_TileType == 6 )
        {
            collisionA.x1 = x;
            collisionA.y1 = y;
            collisionA.x2 = x+tileWidth/1.1;
            collisionA.y2 = y+tileHeight/1.1;
        }
        
    }
    SDL_Rect tileLocation;
    SDL_Rect source;
    int m_TileType;
    int tileID = 0;
    float m_TileAngle = 0.0f;
 
    line collisionA;
    line collisionB;
    
};

class RaceTrack
{
public:
    
    //tilesX = 12 tilesY = 12
    RaceTrack(int tilesX, int tilesY,SDL_Renderer *renderer)
    {
        LoadTrack track("res/track2.txt");
        trackLayout = track.getTrack();
        trackLatSurface = IMG_Load("res/tracklateral.png");
        trackLatTexture = SDL_CreateTextureFromSurface(renderer, trackLatSurface);
        SDL_FreeSurface(trackLatSurface);
        
        
        trackVertSurface = IMG_Load("res/trackvertical.png");
        trackVertTexture = SDL_CreateTextureFromSurface(renderer, trackVertSurface);
        SDL_FreeSurface(trackVertSurface);
        
        trackLRSurface = IMG_Load("res/trackcurved.png");
        trackLRTexture = SDL_CreateTextureFromSurface(renderer, trackLRSurface);
        SDL_FreeSurface(trackLRSurface);
        
        grassSurface = IMG_Load("res/grass.png");
        grassTexture = SDL_CreateTextureFromSurface(renderer, grassSurface);
        SDL_FreeSurface(grassSurface);
        
        trackVertStartSurf = IMG_Load("res/trackverticalstart.png");
        trackVertStart = SDL_CreateTextureFromSurface(renderer, trackVertStartSurf);
        SDL_FreeSurface(trackVertStartSurf);
        
        float tileWidth = 64;
        float tileHeight = 64;
        int tileID = 1;
        for(int i = 0; i < tilesX; i++)
        {
            for(int j = 0; j < tilesY; j++)
            {
                m_Tiles.push_back(Tile(i*tileWidth,j*tileHeight,trackLayout[j][i],tileID));
                if(trackLayout[j][i] == 8)
                {
                    startTile = new Tile(i*tileWidth,j*tileHeight,trackLayout[j][i],tileID);
                }
                tileID++;

            }
        }
        
        std::cout<<"finished loading race track"<<std::endl;
    }
    ~RaceTrack()
    {
        std::cout<<"Calling Racetrack destructor "<<std::endl;
        SDL_DestroyTexture(trackLatTexture);
        SDL_DestroyTexture(trackVertTexture);
        SDL_DestroyTexture(trackLRTexture);
        SDL_DestroyTexture(grassTexture);
        SDL_DestroyTexture(trackVertStart);
        delete[] trackLayout;
        delete currentTile;
        delete startTile;

    }
    void render(SDL_Renderer *renderer);
    void update(Vehicle *car, std::vector<Opponent> &opponents, std::vector<AIVehicle> &aiVehicle);
    Tile* getTileByID(int tileID);
    Tile* getTileByLocation(SDL_Rect rect);
    Tile* getStartTile();
    void checkAllCollisions(AIVehicle *aiVehicle, Tile &tile);

private:
    std::vector<Tile> m_Tiles;
    SDL_Surface *trackLatSurface;
    SDL_Texture *trackLatTexture;
    SDL_Surface *trackVertSurface;
    SDL_Texture *trackVertTexture;
    
    SDL_Surface *trackLRSurface;
    SDL_Texture *trackLRTexture;
    
    SDL_Surface *grassSurface;
    SDL_Texture *grassTexture;
    
    SDL_Surface *trackVertStartSurf;
    SDL_Texture *trackVertStart;
    Tile *currentTile = NULL;
    Tile *startTile = NULL;
    int **trackLayout;
    
};

