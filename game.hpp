//
//  game.hpp
//  RacingV3
//
//  Created by mac on 2023/1/18.
//  Copyright © 2023 Jovian. All rights reserved.
//
#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "objects/vehicle.hpp"
#include "utils/vec2.hpp"
#include "objects/racetrack.hpp"
#include "objects/opponent.hpp"
#include "objects/aivehicle.hpp"
#include "utils/savepath.hpp"
#include "neuralnet/networkfs.hpp"
#define log std::cout<<

class Game
{
public:
    
    Game(float width, float height)
    {
        m_WindowWidth = width;
        m_WindowHeight = height;
        init();
        
    }
    ~Game()
    {
        player = NULL;
        delete raceTrack;
        delete player;
    }
    void init();
    void render();
    void update(float dt);
    void updateControls(SDL_Event *event,const Uint8* m_KeyStates);
    void handleCollisions(Vehicle *car,float dT);
    void handleCollisions(std::vector<Opponent> opponents, std::vector<AIVehicle> aiVehicles);
    void renderWaypoints();
    void updateWaypoints();
    bool getChampion();
public:
    bool running = false;
    bool reset = false;
private:
    bool m_RecordingPath = false;
    bool m_StartRace = false;
    bool createNewBrains = false;
    float m_WindowHeight;
    float m_WindowWidth;
    float timeSinceCrash = 0.0f;
    float coolOffPeriod = 500.0f;
    float timeInSeconds = 0.0f;
    float mutationRate = .02;
    int numOfAI = 500;
    int championCar = 0;  //to keep track of who has the most waypoints completed
    const Uint8 *m_KeyStates;
    SDL_Event m_Event;
    SDL_Renderer *m_Renderer;
    SDL_Surface *carSurface = NULL;
    SDL_Texture *carTexture = NULL;
    RaceTrack *raceTrack = NULL;
    Vehicle *player = NULL;
    std::vector<Opponent> opponents;
    std::vector<Point> path;
    std::vector<AIVehicle> aiVehicles;
    SavePath savePath;
    AIVehicle *quickest = NULL;
    NetworkFS networkFS;
};

