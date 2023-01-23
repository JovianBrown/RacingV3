//
//  loadpath.hpp
//  RacingV2
//
//  Created by mac on 2023/1/14.
//  Copyright © 2023 Jovian. All rights reserved.
//
//Loads a path for the opponents to follow on the track
#pragma once


#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "path.hpp"
class LoadPath
{
public:
    LoadPath()
    {
        std::ifstream myfile("newpathformat.txt");
        std::string line;
        
        if (myfile.is_open())
        {
            int lineNumber = 0;
            std::cout<<"Loading path"<<std::endl;
            while ( getline (myfile,line) )
            {
                lineNumber++;
                Point point;
                if(lineNumber%2 != 0)
                {
                    for(int i = 0; i < line.length();i++)
                    {
                        if(line[i] == ' ')
                        {
                            std::string firstString = line.substr(0,i);
                            std::string secondString = line.substr(i,line.length());
                            float first = std::stof(firstString);
                            float second = std::stof(secondString);
                            point.x = first;
                            point.y = second;
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < line.length();i++)
                    {
                        if(line[i] == ' ')
                        {
                            std::string firstString = line.substr(0,i);
                            std::string secondString = line.substr(i,line.length());
                            float first = std::stof(firstString);
                            float second = std::stof(secondString);
                            point.velocity = first;
                            
                            point.angle = second;
                        }
                    }
                    points.emplace_back(point);
                    numOfPoints++;
                }
           //     std::cout << line << '\n';
                
                
            }
            myfile.close();
        }
        
        else std::cout << "Unable to open savegame";
    }
    std::vector<Point> getPath()
    {
        return points;
    }
    int numOfPoints=0;
    
private:
    std::vector<Point> points;
};
