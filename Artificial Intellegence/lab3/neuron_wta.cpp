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

void Neuron_WTA::change_weight(std::vector<double>& X, double n) {
    for(int i = 0; i < input_num; i++) {
        W[i] = W[i] + n * (X[i] - W[i]);
    }
}

int Neuron_WTA::get_input_num() {
    return input_num;
}

void Neuron_WTA::print_weights(std::ofstream& weights_file) {
        weights_file << W[0] << " " << W[1] << std::endl;
}


void Neuron_WTA::set_rand_W() {
    for(int i = 0; i < input_num; i++) {
        W[i] = rand() % 10;
        W[i] -= 5;
        W[i] /= 10;
    }
    W = vector_normalize(W);
}

void Neuron_WTA::add_win() {
    wins_count++;
}

int Neuron_WTA::get_wins_count() {
    return wins_count;
}

bool Neuron_WTA::win_check(int max_wins, int neuron_num) {
    if ((wins_count < max_wins) && (countdown == 0)) {
        return true;
    } 
    if (wins_count == max_wins) {
        countdown = max_wins * max_wins + neuron_num;
        wins_count = 0;
        return false;
    }
    if (countdown != 0) {
        return false;
    }
    return false;
}

void Neuron_WTA::reduce_countdown() {
    countdown--;
}

int Neuron_WTA::get_countdown() {
    return countdown;
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