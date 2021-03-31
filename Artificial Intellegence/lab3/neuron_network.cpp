#include "neuron_network.hpp"
#define INPUT_NUMS 2
#define N 1.0

Network_WTA::Network_WTA(unsigned int _neuron_num) {
    // Файл для записи вектора выходных данных 
    output_file.open("test.dat");
    if (!output_file) {
        std::cout << "ERROR: can't open file 'test.dat'" << std::endl;
        return;
    }
    neuron_num = _neuron_num;

    srand(time(NULL));
    for(int i = 0; i < _neuron_num; i++) {
        Neuron_WTA Ner(INPUT_NUMS);
        Ner.set_rand_W();
        Neurons.push_back(Ner);
    }

    n = N;
}

Network_WTA::~Network_WTA() {
    output_file.close();
}

// Определение нейрона-победителя и переопределение его весов
void Network_WTA::define_winner(std::vector<double>& X, int iteration) {
    int max_wins = neuron_num;
    double max_output_signal = -10000.0;
    double temp = 0.0;
    int winner_index = 0;
    if (iteration < neuron_num) {
        for(int i = 0; i < Neurons.size(); i++) {
            if (Neurons[i].win_check(max_wins, neuron_num)) {
                temp = Neurons[i].output_signal(X);
                if(temp > max_output_signal) {
                    max_output_signal = temp;
                    winner_index = i;
                }
            } else {
                Neurons[i].reduce_countdown();
            }
        }
    } else {
        for(int i = 0; i < Neurons.size(); i++) {
            temp = Neurons[i].output_signal(X);
            if(temp > max_output_signal) {
                max_output_signal = temp;
                winner_index = i;
            }
        }
    }
    output_file << X[0] << " " << X[1] << " " << winner_index << " " << std::endl;

    Neurons[winner_index].add_win();
    Neurons[winner_index].change_weight(X, n);
    if (n > 0.1) {
        n -= 0.001;
    }
}

void Network_WTA::network_learn(std::vector<std::vector <double> >& X_learn, std::ofstream& weights_file, int age) {
    std::vector<double> X;

    for(int j = 0; j < X_learn.size(); j++) {
        X = Neurons[j].vector_normalize(X_learn[j]);
        print_neurons_weights(weights_file);
        define_winner(X, age);
        weights_file << std::endl;
    }
}

void Network_WTA::print_neurons_weights(std::ofstream& weights_file) {
    for(int i = 0; i < Neurons.size(); i++) {
        Neurons[i].print_weights(weights_file);
    }
}