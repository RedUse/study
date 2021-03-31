#include "neuron_wta.hpp"

Neuron_WTA::Neuron_WTA(int _input_num) {
    input_num = _input_num;
    wins_count = 0;
    countdown = 0;
    W.resize(input_num);
}

double Neuron_WTA::output_signal(std::vector<double>& X) {
    double sum = 0.0;
    for(int i = 0; i < input_num; i++) {
        sum += W[i] * X[i];
    }
    return sum;
}

void Neuron_WTA::change_weights(std::vector<double>& X, double n, double sigma) {
    for(int i = 0; i < input_num; i++) {
        W[i] = W[i] + n * exp(-(distance_to_winner * distance_to_winner) / (2 * sigma * sigma)) * (X[i] - W[i]);
    }
}

int Neuron_WTA::get_input_num() {
    return input_num;
}

int Neuron_WTA::get_countdown() {
    return countdown;
}

int Neuron_WTA::get_wins_count() {
    return wins_count;
}

std::vector<double> Neuron_WTA::get_weights() {
    return W;
}

void Neuron_WTA::print_weights() {
    for(int i = 0; i < W.size(); i++) {
        std::cout << "W" << i+1 << " = " << W[i] << std::endl;
    }
}

void Neuron_WTA::set_distance_to_winner(int _distance) {
    distance_to_winner = _distance;
}

void Neuron_WTA::reduce_countdown() {
    countdown--;
}

bool Neuron_WTA::win_check(int max_wins, int neurons_num) {
    if ((wins_count < max_wins) && (countdown == 0)) {
        return true;
    } 
    if (wins_count == max_wins) {
        countdown = max_wins * max_wins + neurons_num;
        wins_count = 0;
        return false;
    }
    if (countdown != 0) {
        return false;
    }
    return false;
}

int Neuron_WTA::get_distance() {
    return distance_to_winner;
}

void Neuron_WTA::add_win() {
    wins_count++;
}

void Neuron_WTA::set_rand_W() {
    double temp;
    for(int i = 0; i < input_num; i++) {
        W[i] = rand() % 3;
        temp = rand() % 100;
        temp /= 100;
        W[i] -= 1.5;
        W[i] += temp;
    }
    //W = vector_normalize(W);
}

// Нормализация вектора
std::vector<double> Neuron_WTA::vector_normalize(std::vector<double>& _vector) {
    double sum = 0.0;
    std::vector<double> vector = _vector;
    for(int i = 0; i < vector.size(); i++) {
        sum += (vector[i] * vector[i]);
    }
    double root = sqrt(sum);
    for(int i = 0; i < vector.size(); i++) {
        vector[i] /= root;
    }
    return vector;
}

//Эвклидова мера
double Neuron_WTA::calculate_distance(std::vector<double>& _X) {
    double sum = 0.0;
    std::vector<double> X = _X;
    for (int i = 0; i < input_num; i++) {
        sum += ((X[i] - W[i]) * (X[i] - W[i]));
    }
    sum = sqrt(sum);
    return sum;
}

void Neuron_WTA::print_weights(std::ofstream& weights_file) {
        weights_file << W[0] << " " << W[1] << std::endl;
}