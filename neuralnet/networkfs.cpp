//
//  networkfs.cpp
//  RacingV3
//
//  Created by mac on 2023/1/21.
//  Copyright © 2023 Jovian. All rights reserved.
//
// Network file system stuff, save neural network , load neural network

#include "networkfs.hpp"

void NetworkFS::loadNet(NeuralNetwork* network)
{
    std::string line;
    std::ifstream myfile ("brain.txt");
    int currentLine = 0;
    int totalWeights = 0;
    int totalLayers = (int)network->getNetwork().size();
    
    if (myfile.is_open())
    {
      //  std::cout<<"Network FS : total Layers "<<totalLayers<<std::endl;
        for(int i = 0; i < totalLayers; i++)
        {
            for(int j = 0; j < network->getNetwork()[i].inputCount; j++)
            {
                for(int k = 0; k < network->getNetwork()[i].outputCount; k++)
                {
                     totalWeights++;
                }
            }
          //  std::cout<<"Network FS : Total weights for layer "<<i<<": "<<totalWeights<<std::endl;
            totalWeights = 0;
        }
        int weightsL0Size = network->getNetwork()[0].inputCount*network->getNetwork()[0].outputCount;
        int weightsL1Size = network->getNetwork()[1].inputCount*network->getNetwork()[1].outputCount;
        int biasesL0Size = (int)network->getNetwork()[0].getBiases().size();
        int biasesL1Size = (int)network->getNetwork()[1].getBiases().size();
      

        std::vector<float> biasesLayer0;
        std::vector<float> biasesLayer1;
        std::vector<float> weightsLayer0;
        std::vector<float> weightsLayer1;
        
        while ( getline (myfile,line) )
        {
            currentLine++;
            float weight = std::stof(line);
            if(currentLine >= 0 && currentLine <= weightsL0Size)
            {
                weightsLayer0.emplace_back(weight);
            }
            if(currentLine > weightsL0Size && currentLine <= weightsL0Size+weightsL1Size)
            {
                weightsLayer1.emplace_back(weight);
            }
            if(currentLine > weightsL0Size+weightsL1Size && currentLine <= weightsL0Size+weightsL1Size+biasesL0Size)
            {
                biasesLayer0.emplace_back(std::stof(line));
            }
            if(currentLine > weightsL0Size+weightsL1Size+biasesL0Size && currentLine <= weightsL0Size+weightsL1Size+biasesL0Size+biasesL1Size)
            {
               
                biasesLayer1.emplace_back(std::stof(line));
            }
        }
        network->setBiases(biasesLayer0, 0);
        network->setBiases(biasesLayer1, 1);
        network->setWeights(weightsLayer0, 0);
        network->setWeights(weightsLayer1, 1);
      //  std::cout<<"total Biases for layer 0 "<<biasesLayer0.size()<<std::endl;
      //  std::cout<<"total Biases for layer 1 "<<biasesLayer1.size()<<std::endl;
      //  std::cout<<"Number of lines in brain.txt file "<<currentLine<<std::endl;
        myfile.close();
    }
    
    else std::cout << "Unable to open brain, your brain is closed-minded";
}
void NetworkFS::saveNet(NeuralNetwork* network)
{
    std::ofstream saveFile ("brain.txt");
    if (saveFile.is_open())
    {
        for(auto w: network->getNetwork()[0].getWeights())
        {
            saveFile<<w<<"\n";
        }
        for(auto w: network->getNetwork()[1].getWeights())
        {
            saveFile<<w<<"\n";
        }
        for(auto b: network->getNetwork()[0].getBiases())
        {
            saveFile<<b<<"\n";
        }
        for(auto b: network->getNetwork()[1].getBiases())
        {
            saveFile<<b<<"\n";
        }
        std::cout<<"saved network to disk"<<std::endl;
      
    }
}
