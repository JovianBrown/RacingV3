//
//
//  aivehicle.hpp
//  RacingV3
//
//  Created by mac on 2023/1/16.
//  Copyright © 2023 Jovian. All rights reserved.
//

#pragma once
#include <iostream>
#include "vehicle.hpp"
#include "../neuralnet/neuralnetwork.hpp"
#include "../neuralnet/sensor.hpp"
class AIVehicle : public Vehicle
{
public:
    AIVehicle(Vec2 position)
    :Vehicle(position),completedWaypoints(0),currentWaypoint(0)
    {
        sensors = new Sensor(7, 35,getDest()->x,getDest()->y);
        brain = new NeuralNetwork(7, 6, 4);
    }
public:
    void updateAI(float dt);
    void renderSensors(SDL_Renderer *renderer);
    void setAngle(float angle);
    void setCompletedWayPoints(int waypointsCompleted);
    void setCurrentWaypoint(int currentWaypoint);
    int getCompletedWaypoints();
    int getCurrentWaypoint();
    
    Sensor *getSensors();
    NeuralNetwork *getBrain();
    
private:
    Sensor *sensors = NULL;
    NeuralNetwork *brain = NULL;
    std::vector<float> outputs;
    std::vector<float> offsets;
    int completedWaypoints;
    int currentWaypoint;
private:
    void moveAI(std::vector<float> outputs);

};
