//
//  path.hpp
//  RacingV2
//
//  Created by mac on 2023/1/14.
//  Copyright © 2023 Jovian. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
struct Point
{
    float angle;
    float x;
    float y;
    float velocity;
    Point(float x, float y, float angle, float velocity)
    {
        this->x = x;
        this->y = y;
        this->velocity = velocity;
        this->angle = angle;
    }
    Point()
    {
        
    }
};

class Path
{
public:
    Path()
    {
        
    }
    void addPoint(float x, float y, float angle, float velocity)
    {
        points.push_back(Point(x,y,angle,velocity));
        
    }
    std::vector<Point> getPath()
    {
        return points;
    }
private:
    std::vector<Point> points;
};
