//
//  loadtrack.hpp
//  Racing
//
//  Created by mac on 2022/12/26.
//  Copyright © 2022 Jovian. All rights reserved.
//

#ifndef loadtrack_hpp
#define loadtrack_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>


class LoadTrack
{
public:
    LoadTrack(std::string filename)
    {
        std::string line;
        std::ifstream myfile(filename);
        int width = 12;
        int height = 12;
        trackLayout = new int*[width];
        for(int i = 0; i < width; i++)
        {
            trackLayout[i] = new int[height];
        }
        
        if (!myfile.is_open())
        {
            std::cout<<"Error opening file"<<std::endl;
        }
        for(int i = 0; i < width; i++)
        {
            for(int j = 0; j < height; j++)
            {
                myfile >> trackLayout[i][j];
            }
        }
        
        
    }
    ~LoadTrack()
    {
        std::cout<<"Calling loadtrack destructor"<<std::endl;
        delete[] trackLayout;
    }
    int ** getTrack()
    {
        return trackLayout;
    }
private:
    int **trackLayout;
};
#endif /* loadtrack_hpp */
