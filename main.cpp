//
//  main.cpp
//  RacingV3
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include <iostream>
#include "game.hpp"
#include <SDL2/SDL.h>
static const int windowWidth = 768;
static const int windowHeight = 768;
int main(int argc, const char * argv[])
{
   
    Uint32 lastUpdate = SDL_GetTicks();
    float elapsedSeconds = 0.0f;
    Uint32 current;
    float dT;
    Game game(windowWidth,windowHeight);
    while(game.running)
    {
        current = SDL_GetTicks();
        dT = (current - lastUpdate) / 1000.0f;
        game.update(dT*10);
        game.render();
        elapsedSeconds += dT;
        if(elapsedSeconds >= 1)
        {
            elapsedSeconds = 0;
           // std::cout<<"Tick"<<std::endl;
        }
        lastUpdate = current;
        if(game.reset)
        {
            game.~Game();
        }
    }
    
    return 0;
}
