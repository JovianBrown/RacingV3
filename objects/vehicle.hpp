
#pragma once

#include <stdio.h>
#include <iostream>
#include "../utils/vec2.hpp"
//#include "racetrack.hpp"
//#include "racetrack.hpp"
//#define MAX_VELOCITY 5.5
//#define MIN_VELOCITY -2.5

#define MAX_ACCEL 500
#define MIN_ACCEL -280
#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 768
class Vehicle
{
public:
    Vehicle(Vec2 position)
    :m_Drag(0.01),m_TurnAngle(2.0),m_Mass(1200),m_Angle(0.0),m_MaxVelocity(1.4),m_MinVelocity(-1.2)
    {
        x = position.x;
        y = position.y;
        position.x = x;
        position.y = y;
        source.x = 0;
        source.y = 0;
        source.w = 80;
        source.h = 192;
        m_Velocity.x = 0.0;
        m_Velocity.y = 0.0;
        m_AccelForce = Vec2(0.0,7.5);
        m_Force = Vec2();
        dest = new SDL_Rect();
        dest->x = x;
        dest->y = y;
        dest->w = 0;
        dest->h = 0;
    }
    ~Vehicle()
    {
        
    }
    void render(SDL_Renderer *renderer,SDL_Texture *carTexture);
    void update(float dt);
    void move();
    void setVelocity(Vec2 vec);
    void setForce(Vec2 vec);
    void setDest(float x, float y);
    void setDrag(float drag);
    void setMaxVelocity(float maxVelocity);
    Vec2 getPosition();
    int getCurrentTile()
    {
        return currentTile;
    }
    void setCurrentTile(int currentTile)
    {
        this->currentTile = currentTile;
    }
    Vec2 getVelocity();
    Vec2& getForce();
    const float getAngle();
    SDL_Rect * getDest()
    {
        return dest;
    }
    float getMass()
    {
        return m_Mass;
    }
    void setChampion(bool champion);
    bool getChampion();
public:
    Vec2 position;
    bool forward = false;;
    bool reverse = false;
    bool left = false;
    bool right = false;
    bool collided = false;
    float m_Angle;
    
    ///////
    //  void setCurrentTile(Tile &t);
private:
    SDL_Rect source;
    float x;
    float y;
    float m_Mass;
    float m_TurnAngle;
    float m_Drag;
    float m_MaxVelocity;
    float m_MinVelocity;
    SDL_Rect *dest;
    Vec2 m_Velocity;
    Vec2 m_Force;  //current sigma force
    Vec2 m_AccelForce;  //how much horsepower
    int currentTile = 0;
    bool isChampion = false;
    /// new stuff below
    u_int8_t gear;
    float m_Traction = 1.0;
    ///////
private:
    void limitVelocity();
    void applyDrag();
    void limitAcceleration();
    void changeGears();
    
};
