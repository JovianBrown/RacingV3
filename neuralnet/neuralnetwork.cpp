//
//  neuralnetwork.cpp
//  RacingV3
//
//  Created by mac on 2023/1/16.
//  Copyright © 2023 Jovian. All rights reserved.
//

#include "neuralnetwork.hpp"

void Layer::generateBiases()
{
    for(int i = 0; i < outputCount; i++)
    {
        biases.push_back(getRandom());
    }
}
void Layer::generateWeights()
{
    for(int i = 0; i < inputCount; i++)
    {
        for(int j = 0; j < outputCount; j++)
        {
            weights[i][j] = getRandom();
        }
    }
}
std::vector<float> Layer::getWeights()
{
    std::vector<float> saveWeights;
    
    for(int i = 0; i < inputCount; i++)
    {
        for(int j = 0; j < outputCount; j++)
        {
            saveWeights.emplace_back(weights[i][j]);
        }
    }
    return saveWeights;
}

std::vector<float> Layer::getBiases()
{
    return biases;
}
std::vector<float> Layer::feedForward(std::vector<float> givenInputs, Layer layer ) //giveninputs are from the sensors
{
    for(int i = 0; i < layer.inputCount; i++)
    {
        inputs.push_back(givenInputs[i]);
    }
    for(int i = 0; i < layer.outputCount; i++)
    {
        float sum = 0.0;
        for(int j = 0; j < layer.inputCount; j++)
        {
            sum+=inputs[j]*weights[j][i];
        }
        if(sum>biases[i])
        {
            outputs.push_back(1.0);
            
        }
        else
        {
            outputs.push_back(0.0);
        }
    }
    return outputs;
}

float Layer::getRandom()
{
    int negative = rand()%100;
    float randomFloat = rand() / static_cast<float>(RAND_MAX);
    if(negative > 50)
    {
        return -1*randomFloat;
    }
    return randomFloat;
}

////////////////////


std::vector<Layer> NeuralNetwork::getNetwork()
{
    return layers;
}
std::vector<float> NeuralNetwork::feedForward(std::vector <float> givenInputs, NeuralNetwork network)
{
    std::vector<float> outputs;
    outputs = network.layers[0].feedForward(givenInputs, network.layers[0]);
    for(int i = 1; i <network.layers.size(); i++)
    {
        outputs = network.layers[i].feedForward(outputs, network.layers[i]);
    }
    return outputs;
}
void NeuralNetwork::mutate(NeuralNetwork *neuralNetwork, float amount = 1.0)
{
  //  std::cout<<"Amount to mutate : "<<amount<<std::endl;
    for(int i = 0; i < neuralNetwork->layers.size(); i++)
    {
        for(int j = 0; j < neuralNetwork->layers[i].getBiases().size(); j++)
        {
      //      std::cout<<"Previous Bias "<<neuralNetwork->layers[i].biases[j]<<std::endl;
            neuralNetwork->layers[i].biases[j] = LERP(neuralNetwork->layers[i].biases[j], neuralNetwork->layers[i].getRandom(), amount);
        //    std::cout<<"Mutated Bias "<<neuralNetwork->layers[i].biases[j]<<std::endl;

        }
        
        for(int j = 0; j < neuralNetwork->layers[i].inputCount; j++)
        {
            for(int k = 0; k < neuralNetwork->layers[i].outputCount; k++)
            {
         //       std::cout<<"Previous Weights "<<neuralNetwork->layers[i].weights[j][k]<<std::endl;

                 neuralNetwork->layers[i].weights[j][k]= LERP(neuralNetwork->layers[i].weights[j][k], neuralNetwork->layers[i].getRandom(), amount);
          //      std::cout<<"Mutated Weights "<<neuralNetwork->layers[i].weights[j][k]<<std::endl;

            }
        }
    }
    
}
void NeuralNetwork::printBrain(NeuralNetwork *neuralNetwork)
{
    std::cout<<"weights"<<std::endl;

    for(auto &w: neuralNetwork->layers[0].getWeights())
    {
        std::cout<<"w :"<<w<<std::endl;
    }
    for(auto &w: neuralNetwork->layers[1].getWeights())
    {
        std::cout<<"w :"<<w<<std::endl;
    }
    
}
void NeuralNetwork::setBiases(std::vector<float> storedBiases, int layerNumber)
{
    layers[layerNumber].biases = storedBiases;
//    for(auto &b: layers[layerNumber].biases)
//    {
//        std::cout<<"set bias from setBiases value: "<<b<<std::endl;
//    }
}
void NeuralNetwork::setWeights(std::vector<float> weights,int layerNumber)
{
    int currentWeightIndex = 0;
    for(int i = 0; i < layers[layerNumber].inputCount; i++)
    {
        for(int j = 0; j < layers[layerNumber].outputCount; j++)
        {
            layers[layerNumber].weights[i][j] = weights[currentWeightIndex];
            currentWeightIndex++;
        }
    }

}

