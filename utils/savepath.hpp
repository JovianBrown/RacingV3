//
//  savepath.hpp
//  RacingV2
//
//  Created by mac on 2023/1/14.
//  Copyright © 2023 Jovian. All rights reserved.
//
// this is to record path vectors for the opponents to follow on the track
#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "path.hpp"
class SavePath
{
    
public:
    //   SavePath(std::vector<Vec3> path)
    SavePath()
    {
        
    }
    void save(std::vector<Point> path);
    
private:
    std::vector<Point> path;
};
