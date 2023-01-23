//
//  aivehicle.cpp
//  RacingV2
//
//  Created by mac on 2023/1/16.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "aivehicle.hpp"
void AIVehicle::updateAI(float dt)
{
    Vec2 rayPosition;
    offsets.clear();
    rayPosition.x = getDest()->x+getDest()->w/2;
    rayPosition.y = getDest()->y+getDest()->h/2;
    sensors->update(rayPosition.x, rayPosition.y, getAngle());
    offsets = sensors->getReadings();
    outputs = brain->feedForward(offsets, *brain);
    moveAI(outputs);
   
}
void AIVehicle::moveAI(std::vector<float> outputs)
{
    if(collided == false)
    {
        forward = outputs[0];
        reverse = outputs[1];
        left = outputs[2];
        right = outputs[3];
    }
    
}
void AIVehicle::renderSensors(SDL_Renderer *renderer)
{
    if(!collided)
        sensors->render(renderer);
}
Sensor * AIVehicle::getSensors()
{
    return sensors;
}
void AIVehicle::setAngle(float angle)
{
    this->m_Angle = angle;
}
NeuralNetwork * AIVehicle::getBrain()
{
    return this->brain;
}
void AIVehicle::setCompletedWayPoints(int waypointsCompleted)
{
    completedWaypoints = waypointsCompleted;
}
int AIVehicle::getCompletedWaypoints()
{
    return completedWaypoints;
}
int AIVehicle::getCurrentWaypoint()
{
    return currentWaypoint;
}
void AIVehicle::setCurrentWaypoint(int currentWaypoint)
{
    this->currentWaypoint = currentWaypoint;
}
