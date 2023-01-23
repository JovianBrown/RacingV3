//
//  opponent.hpp
//  RacingV3
//
//  Created by mac on 2023/1/12.
//  Copyright © 2023 Jovian. All rights reserved.
//

#ifndef opponent_hpp
#define opponent_hpp

#include <stdio.h>
#include "vehicle.hpp"
#include "../utils/vec2.hpp"
#include "../utils/path.hpp"
#include <vector>
#include "../utils/loadpath.hpp"
#include "../utils/utils.hpp"
class Opponent : public Vehicle
{
public:
    Opponent(Vec2 position)
    :Vehicle(position)
    {
        LoadPath lp; //load
        path = lp.getPath();
        numOfPoints = lp.numOfPoints;
    }
public:
    void updateWayPoint();
    void renderWaypoint(SDL_Renderer *renderer);
private:
    std::vector<Point> path;
    int numOfPoints;
    int wayPointIndex = 0;
    float waypointX = 0;
    float waypointY = 0;
  //  Vec3 currentWayPointVec;
};
#endif /* opponent_hpp */
