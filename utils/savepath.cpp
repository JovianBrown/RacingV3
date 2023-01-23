//
//  savepath.cpp
//  RacingV2
//
//  Created by mac on 2023/1/14.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "savepath.hpp"


void SavePath::save(std::vector<Point> path)
{
    this->path = path;
    std::ofstream pathSaveFile ("newpathformat.txt");
    if (pathSaveFile.is_open())
    {
        for(auto &p: path)
        {
            pathSaveFile << p.x <<" "<<p.y<<"\n"<<p.velocity<<" "<<p.angle<<"\n";
        }
        pathSaveFile.close();
    }
    else
    {
        std::cout << "Unable to open save file"<<std::endl;
    }
    
}
