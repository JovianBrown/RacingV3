//
//  networkfs.hpp
//  RacingV3
//
//  Created by mac on 2023/1/21.
//  Copyright © 2023 Jovian. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "neuralnetwork.hpp"
class NetworkFS
{
public:
    NetworkFS()
    {
    }
    ~NetworkFS()
    {
        
    }
    void loadNet(NeuralNetwork* network);
    void saveNet(NeuralNetwork* network);
private:
    float** weights;

};

