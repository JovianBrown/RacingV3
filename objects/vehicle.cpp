
//  vehicle.cpp
//  RacingV3
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "vehicle.hpp"
void Vehicle::update(float dt)
{
    if(!collided)
    {
        m_Angle = fmod(m_Angle,360);
        m_Velocity.x = m_Velocity.x+(m_Force.x/m_Mass)*dt;
        m_Velocity.y = m_Velocity.y+(m_Force.y/m_Mass)*dt;
        
        x = x+(sin(m_Angle*0.01745))*m_Velocity.y;
        y = y-(cos(m_Angle*0.01745))*m_Velocity.y;
        position.x = x;
        position.y = y;
        move();
        limitVelocity();
        applyDrag();
        limitAcceleration();
        if(getDest()->x < 0 || getDest()->y < 0 || getDest()->x > WINDOW_WIDTH || getDest()->y > WINDOW_HEIGHT)  //vehicle out of bounds
        {
            collided = true;
        }
        
       
    }
   
}


void Vehicle::move()
{
    if(forward)
    {
        //   std::cout<<"Force Vector"<<m_Force<<std::endl;
        //   std::cout<<"Velocity Vector"<<m_Velocity<<std::endl;
        
        m_Force = m_Force.add(m_AccelForce);
    }
    if(reverse)
    {
        m_Force = m_Force.subtract(m_AccelForce);
    }
    if(!forward && !reverse)
    {
        m_Force.y = 0;
        m_Force.x = 0;
    }
    if(left)
    {
        m_Angle-=m_TurnAngle;
        
    }
    if(right)
    {
        m_Angle+=m_TurnAngle;
    }
}
void Vehicle::applyDrag()
{
    if(m_Velocity.magnitude() > 0)
    {
        if(m_Velocity.x > 0 )
        {
            m_Velocity.x -=m_Drag;
        }
        if(m_Velocity.x < 0 )
        {
            m_Velocity.x +=m_Drag;
        }
        if(m_Velocity.y > 0 )
        {
            m_Velocity.y -=m_Drag;
        }
        if(m_Velocity.y < 0 )
        {
            m_Velocity.y +=m_Drag;
        }
        if(m_Velocity.magnitude() < m_Drag)
        {
            m_Velocity = Vec2();
        }
    }
    
}
void Vehicle::limitAcceleration()
{
    if(m_Force.y > MAX_ACCEL)
    {
        m_Force.y = MAX_ACCEL;
        
    }
    if(m_Force.y < MIN_ACCEL)
    {
        m_Force.y = MIN_ACCEL;
    }
}
void Vehicle::limitVelocity()
{
    
    if(m_Velocity.magnitude() > m_MaxVelocity)
    {
        if(m_Velocity.x> m_MaxVelocity)
        {
            m_Velocity.x  = m_MaxVelocity;
        }
        if(m_Velocity.y > m_MaxVelocity)
        {
            m_Velocity.y = m_MaxVelocity;
        }
    }
    if(m_Velocity.x < m_MinVelocity)
    {
        m_Velocity.x = m_MinVelocity;
    }
    if(m_Velocity.y < m_MinVelocity)
    {
        m_Velocity.y = m_MinVelocity;
        
    }
}
void Vehicle::render(SDL_Renderer *renderer, SDL_Texture *carTexture)
{
    
    
    dest->x = x;
    dest->y = y;
    dest->w = 10;
    dest->h = 24;
   
    if(!collided)
    {
        SDL_RenderCopyEx(renderer, carTexture, &source, dest, m_Angle, NULL, SDL_FLIP_NONE);
    }
    if(isChampion)
    {
        SDL_SetRenderDrawColor(renderer, 0, 200, 200, 255);
        SDL_RenderDrawRect(renderer, dest);
    }
}
Vec2 Vehicle::getPosition()
{
    return position;
}

Vec2 Vehicle::getVelocity()
{
    return m_Velocity;
}
void Vehicle::setVelocity(Vec2  vec)
{
    m_Velocity = vec;
}
void Vehicle::setForce(Vec2 vec)
{
    m_Force = vec;
}
void Vehicle::setDest(float x, float y)
{
    dest->x = x;
    dest->y = y;
}
void Vehicle::setDrag(float drag)
{
    m_Drag = drag;
}
void Vehicle::setMaxVelocity(float maxVelocity)
{
    m_MaxVelocity = maxVelocity;
}
Vec2& Vehicle::getForce()
{
    return m_Force;
}
const float Vehicle::getAngle()
{
    return m_Angle;
}
void Vehicle::setChampion(bool champion)
{
    isChampion = champion;
}
bool Vehicle::getChampion()
{
    return isChampion;
}


