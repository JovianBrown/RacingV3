//
//  neuralnetwork.hpp
//  RacingV2
//
//  Created by mac on 2023/1/16.
//  Copyright © 2023 Jovian. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include "../utils/utils.hpp"
class Layer
{
public:
    Layer(int inputCount, int outputCount)
    {
        this->inputCount = inputCount;
        this->outputCount = outputCount;
        weights = new float*[inputCount];
        for (int i = 0; i < inputCount; i++)  
        {
            weights[i] = new float[outputCount];
        }
        generateWeights();
        generateBiases();
    }
    void generateWeights();                //creates values for weights
    void generateBiases();                 //creates values for biases
    std::vector<float> getWeights();  //for saving to filesystem (networkfs)
    std::vector<float> getBiases();   //for saving to filesystem (networkfs)
    std::vector<float> feedForward(std::vector<float> givenInputs, Layer layer); 
    float getRandom(); //gets random value between -1 and 1
public:
    float** weights;
    std::vector<float> biases;
    int inputCount=0;
    int outputCount=0;
private:
    std::vector<float> inputs;
    std::vector<float> outputs;
    
};
class NeuralNetwork
{
public:
    NeuralNetwork(int inputCount, int hiddenLayers, int outputLayers)  //5 , 6, 4
    {
        layers.push_back(Layer(inputCount,hiddenLayers));
        layers.push_back(Layer(hiddenLayers,outputLayers));
    }
    NeuralNetwork();
    std::vector<Layer> getNetwork();
    std::vector<float> feedForward(std::vector <float> givenInputs, NeuralNetwork network);
    void mutate(NeuralNetwork *neuralNetwork, float amount);
    void setWeights(std::vector<float> weights, int layerNumber);
    void setBiases(std::vector<float> storedBiases , int layerNumber);
    void printBrain(NeuralNetwork *neuralNetwork);
private:
    int neuronCount;
    std::vector<Layer> layers;
};
