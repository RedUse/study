#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include "neuron_wta.hpp"
#define CLASSES_NUM 2

class Network_WTA {
 private:
    std::vector<Neuron_WTA> Neurons;
    std::ofstream output_file;
    unsigned int neuron_num;
    double n;
 public:
    Network_WTA(unsigned int _neuron_num);
    ~Network_WTA();
    void define_winner(std::vector<double>& _X, int _iteration);
    void network_learn(std::vector<std::vector <double> >& X_learn, std::ofstream& weights_file, int _age);
    void print_neurons_weights(std::ofstream& _file);
};