//
//  game.cpp
//  RacingV3
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "game.hpp"

void Game::init()
{
    
    SDL_Window* m_Window;
    m_Window = SDL_CreateWindow("RacingV3",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,m_WindowWidth,m_WindowHeight,SDL_WINDOW_METAL);
    if(m_Window!=NULL)
        log "Window created"<<std::endl;
    else
        log "Unable to create window! "<<SDL_GetError()<<std::endl;
    
    m_Renderer = SDL_CreateRenderer(m_Window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_RenderGetMetalLayer(m_Renderer);
    if(m_Renderer!=NULL)
        log "renderer created"<<std::endl;
    else
        log "Failed to create renderer"<<SDL_GetError()<<std::endl;
    
    SDL_PLATFORM_SUPPORTS_METAL;
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    SDL_Init(SDL_INIT_EVERYTHING);
    
    //////  END of SDL Init STUFF////////
    srand(SDL_GetTicks());

    running = true;
    raceTrack = new RaceTrack(12, 12, m_Renderer);
    if(raceTrack->getStartTile())
    {
        log "Start tile "<<raceTrack->getStartTile()->tileLocation.x<<" "<<raceTrack->getStartTile()->tileLocation.y<<std::endl;
    }
    else
    {
        log "failed to load start tile "<<std::endl;
    }
    player = new Vehicle(Vec2(raceTrack->getStartTile()->tileLocation.x,raceTrack->getStartTile()->tileLocation.y));
    carSurface = IMG_Load("res/redcartires.png");
    carTexture = SDL_CreateTextureFromSurface(m_Renderer, carSurface);
    if(carTexture == NULL)
    {
        log "Failed to load car texture"<<std::endl;
    }
    for(int i = 0; i < numOfAI; i++)
    {
        aiVehicles.push_back(AIVehicle(Vec2(raceTrack->getStartTile()->tileLocation.x+20,raceTrack->getStartTile()->tileLocation.y+40)));
    }
    for(int i = 0; i < 0; i++)
    {
        opponents.push_back(Opponent(Vec2(raceTrack->getStartTile()->tileLocation.x+i*20,raceTrack->getStartTile()->tileLocation.y-20)));
        
    }
    log "Loading Neural Network"<<std::endl;
    LoadPath lp; //load path for waypoints
    path = lp.getPath();
    if(!createNewBrains)
    {
        std::cout<<"Mutating"<<std::endl;

        for(int i = 0; i < numOfAI; i++)
        {
            if(i !=0)
            {
                networkFS.loadNet(aiVehicles[i].getBrain());
                aiVehicles[i].getBrain()->mutate(aiVehicles[i].getBrain(), mutationRate);
            }
            else
            {
                networkFS.loadNet(aiVehicles[i].getBrain());
            }
        }
    }
}
void Game::update(float dt)
{
    m_KeyStates = SDL_GetKeyboardState(NULL);
    SDL_PollEvent(&m_Event);
    updateControls(&m_Event, m_KeyStates);
    timeInSeconds +=dt;
    if(timeInSeconds >= 4)
    {
        timeInSeconds = 0.0f;
        for(auto &ai: aiVehicles)
        {
            if(!ai.collided)
            {
                if(ai.getCompletedWaypoints() >= championCar)
                {
                    championCar = ai.getCompletedWaypoints();
                    quickest = &ai;
                    ai.setChampion(true);
                }
                else
                {
                    ai.setChampion(false);
                }
            }
        }
     //   log "Champion Car Completed waypoints: "<<championCar<<std::endl;
        if(m_RecordingPath)
        {
            
            path.push_back(Point(player->getPosition().x,player->getPosition().y,player->getAngle(),player->getVelocity().magnitude()));
            log "pushing back point "<<player->getPosition().x<<" , "<<player->getPosition().y<<std::endl;
        }
    }
    player->update(dt);
    for(int i = 0; i < aiVehicles.size(); i++)
    {
        aiVehicles[i].update(dt);
        aiVehicles[i].updateAI(dt);
        if(aiVehicles[i].collided)
        {
            aiVehicles.erase( aiVehicles.begin() + i );
          //  log "AI Vehicles vector size: "<<aiVehicles.size()<<std::endl;
        }
    }
    updateWaypoints();
    raceTrack->update(player, opponents, aiVehicles);
    for(auto &o: opponents)
    {
        
        o.updateWayPoint();
        if(m_StartRace)
        {
            o.update(dt);
        }
    }
    handleCollisions(player, dt);
    if(player->collided && SDL_GetTicks() > timeSinceCrash + coolOffPeriod  )
    {
        player->collided = false;
    }
}
void Game::render()
{
    SDL_RenderClear(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 0, 100, 10, 255);
    raceTrack->render(m_Renderer);
    renderWaypoints();
    for(auto &o: opponents)
    {
        o.render(m_Renderer,carTexture);
        o.renderWaypoint(m_Renderer);
    }
    player->render(m_Renderer,carTexture);
    for(auto &ai: aiVehicles)
    {
        
        ai.render(m_Renderer, carTexture);
        if(ai.getChampion())
        {
            ai.renderSensors(m_Renderer);
        }
    }
    
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderPresent(m_Renderer);
    
}
void Game::updateControls(SDL_Event *event,const Uint8* m_KeyStates)
{
    
    if(event->type == SDL_QUIT)
    {
        running = false;
        
    }
    if(event->type == SDL_KEYDOWN)
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_q:
                running = false;
                break;
            case SDLK_w:
                player->forward = true;
                log "player acceleration "<<player->getForce()<<std::endl;
                break;
            case SDLK_s:
                player->reverse = true;
                break;
            case SDLK_a:
                player->left = true;
                break;
            case SDLK_d:
                player->right = true;
                break;
            case SDLK_r:
                reset = true;
                break;
        /*    case SDLK_i:
                camera->up = true;
                break;
            case SDLK_k:
                camera->down = true;
                break;
            case SDLK_j:
                camera->left = true;
                break;
            case SDLK_l:
                camera->right = true;
                break;
            case SDLK_z:
                camera->setZoom(camera->m_Zoom+0.5);
                break;
            case SDLK_x:
                camera->setZoom(camera->m_Zoom-0.5);
                break; */
            case SDLK_1:
                log "Start recording path"<<std::endl;
                m_RecordingPath = true;
                break;
            case SDLK_2:
                savePath.save(path);
                log "Calling save path"<<std::endl;
                break;
            case SDLK_3:
             //   m_StartRace = true;
             //   log "start race!"<<std::endl;
               // SaveNetwork saveNetwork(quickest->getBrain());
                networkFS.saveNet(quickest->getBrain());
                std::cout<<"Saving champion, position xy: " <<quickest->getDest()->x<<" , "<<quickest->getDest()->y<<std::endl;
                break;
            case SDLK_4:
                aiVehicles[0].getBrain()->printBrain(aiVehicles[0].getBrain());
                break;
            case SDLK_5:
                aiVehicles[1].getBrain()->printBrain(aiVehicles[1].getBrain());
                break;
                
        }
        
        
    }
    if(event->type == SDL_KEYUP)
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_w:
                player->forward = false;
                break;
            case SDLK_s:
                player->reverse = false;
                break;
            case SDLK_a:
                player->left = false;
                break;
            case SDLK_d:
                player->right = false;
                break;
      /*      case SDLK_i:
                camera->up = false;;
                break;
            case SDLK_k:
                camera->down = false;;
                break;
            case SDLK_j:
                camera->left = false;;
                break;
            case SDLK_l:
                camera->right = false;;
                break; */
        }
    }
}
void Game::updateWaypoints()
{
    for(auto &ai: aiVehicles)
    {
        Vec2 waypointVec = Vec2(path[ai.getCurrentWaypoint()].x,path[ai.getCurrentWaypoint()].y);
        float wayPointDistance = waypointVec.distance(Vec2(ai.getDest()->x,ai.getDest()->y));
      //  std::cout<<"Waypoint distance "<<wayPointDistance<<std::endl;
        if(wayPointDistance < 15)
        {
            ai.setCompletedWayPoints(ai.getCompletedWaypoints()+1);
            ai.setCurrentWaypoint(ai.getCurrentWaypoint()+1);
        }
        
    }
}
void Game::renderWaypoints()
{
    for(int i = 0; i < path.size(); i++)
    {
        SDL_Rect waypointRect;
        waypointRect.x = path[i].x;
        waypointRect.y = path[i].y;
        waypointRect.w = 10;
        waypointRect.h = 10;
        SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(m_Renderer, &waypointRect);
     
    }
}
void Game::handleCollisions(std::vector<Opponent> opponents, std::vector<AIVehicle> aiVehicles)
{
    for(auto &o: opponents)
    {
        for(auto &a: aiVehicles)
        {
            if(checkCollision(*o.getDest(), *a.getDest()))
            {
                timeSinceCrash = SDL_GetTicks();
                a.collided = true;
                o.collided = true;
                a.setVelocity(Vec2(a.getVelocity().x*-1,a.getVelocity().y*-1));
                o.setVelocity(Vec2(o.getVelocity().x*-1,o.getVelocity().y*-1));
                o.setForce(Vec2());
            }

        }
    }
}

void Game::handleCollisions(Vehicle *car,float dT)
{
    
    for(auto &o: opponents)
    {
        if(checkCollision(*player->getDest(), *o.getDest()) && !player->collided && (player->getVelocity().magnitude()>0 || o.getVelocity().magnitude()>0))
        {
            timeSinceCrash = SDL_GetTicks();
            player->collided = true;
            o.collided = true;
            Vec2 impactVelocity = player->getVelocity().add(o.getVelocity());
            log "Impact velocity"<<impactVelocity<<std::endl;
            player->setVelocity(Vec2(player->getVelocity().x*-1,player->getVelocity().y*-1));
            player->setForce(Vec2());
            // o.setVelocity(Vec2(o.getVelocity().x*-1,o.getVelocity().y*-1));
            o.setForce(Vec2());
           
        }
    }
    
}
