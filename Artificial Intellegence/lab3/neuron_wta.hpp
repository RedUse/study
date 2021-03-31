#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <fstream>

class Neuron_WTA {
 private:
    std::vector<double> W;
    int input_num;
    int wins_count;
    int countdown;
 public:
    Neuron_WTA(int _input_num);
    void add_win();
    void reduce_countdown();
    bool win_check(int _max_wins, int _neuron_num);
    int get_wins_count();
    int get_countdown();
    double output_signal(std::vector<double>& _X);
    void change_weight(std::vector<double>& _X, double n);
    int get_input_num();
    void print_weights(std::ofstream& _file);
    void set_rand_W();
    std::vector<double> vector_normalize(std::vector<double>& _vector);
};
