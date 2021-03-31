#include "neuron_network.hpp"
#define INPUT_NUMS 2
#define N 1.0
#define SIGMA 1.0
#define SWK 14

Network_WTA::Network_WTA(unsigned int _neuron_num) {
    // Файл для записи выходных данных 
    output_file.open("test.dat");
    if (!output_file) {
        std::cout << "ERROR: can't open file 'test.dat'" << std::endl;
        return;
    }

    srand(time(NULL));
    for(int i = 0; i < _neuron_num; i++) {
        Neuron_WTA Ner(INPUT_NUMS);
        Ner.set_rand_W();
        Neurons.push_back(Ner);
    }

    n = N;
    sigma = SIGMA;
    Swk = Neurons.size();
}

Network_WTA::~Network_WTA() {
    output_file.close();
}

// Определение нейрона-победителя и переопределение его весов
int Network_WTA::define_winner(std::vector<double>& X, int iteration) {
    int max_wins = Neurons.size();
    double min_distance = 100000.0;
    double temp_distance = -10000.0;
    int winner_index = 0;
    if (iteration < 1) {
        for(int i = 0; i < Neurons.size(); i++) {
            if (Neurons[i].win_check(max_wins, Neurons.size())) {
                temp_distance = Neurons[i].calculate_distance(X);
                if(temp_distance < min_distance) {
                    min_distance = temp_distance;
                    winner_index = i;
                }
            } else {
                Neurons[i].reduce_countdown();
            }
        }
    } else {
        for(int i = 0; i < Neurons.size(); i++) {
            temp_distance = Neurons[i].calculate_distance(X);
            if(temp_distance < min_distance) {
                min_distance = temp_distance;
                winner_index = i;
            }
        }
    }
    output_file << X[0] << " " << X[1] << " " << winner_index << " " << std::endl;
    return winner_index;
}

void Network_WTA::calculate_distance_to_winner(std::vector<double>& X, int winner_index) {
    int distance = 0;
    for (int i = 0; i < Neurons.size(); i++) {
        Neurons[i].set_distance_to_winner(abs(winner_index - i));
    }
}

void Network_WTA::check_koeffs() {
    if(n > 0.08) {
        n -= 0.0007;
    } else {
        n = 0.08;
    }
    if(sigma > 0.06) {
        sigma -= 0.0007;
    } else {
        sigma = 0.06;
    }
    if (Swk > 2) {
        Swk -= 1;
    } else {
        Swk = 2;
    }
}
void Network_WTA::network_learn(std::vector<std::vector <double> >& X_learn, std::ofstream& weights_file, int age) {
    std::vector<double> X;
    int winner_index;

    for(int i = 0; i < X_learn.size(); i++) {
        //X = Neurons[i].vector_normalize(X_learn[i]);
        X = X_learn[i];
        winner_index = define_winner(X, age);
        Neurons[winner_index].add_win();
        calculate_distance_to_winner(X, winner_index);
        for(int j = 0; j < Neurons.size(); j++) {
            if(Neurons[j].get_distance() < Swk) {
                Neurons[j].change_weights(X, n, sigma);
            }
        }
        print_neurons_weights(weights_file);
        weights_file << std::endl;
        check_koeffs();
    }
}

void Network_WTA::print_neurons_weights(std::ofstream& weights_file) {
    for(int i = 0; i < Neurons.size(); i++) {
        Neurons[i].print_weights(weights_file);
    }
}