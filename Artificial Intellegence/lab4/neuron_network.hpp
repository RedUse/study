#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "neuron_wta.hpp"
#define CLASSES_NUM 10

class Network_WTA {
 private:
    std::vector<Neuron_WTA> Neurons;
    std::ofstream output_file;
    double n;
    double sigma;
    int Swk;
 public:
    Network_WTA(unsigned int _neuron_num);
    ~Network_WTA();
    int define_winner(std::vector<double>& _X, int iteration);
    void network_learn(std::vector<std::vector <double> >& X_learn, std::ofstream& weights_file, int age);
    void print_neurons_weights(std::ofstream& _file);
    void calculate_distance_to_winner(std::vector<double>& _X, int _winner_index);
    void check_koeffs();
};