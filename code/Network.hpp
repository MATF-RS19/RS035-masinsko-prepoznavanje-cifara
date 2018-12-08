#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__ 1

class network{
public:
    network(std::vector<size_t>& topology, double learning_rate);
    double learning_rate() const=0;
    void set_learning_rate(double learning_rate);
    const std::vector<double>& estimate() const=0;
    bool feed(const std::vector<double>& input_values);
    void descend();
    void reset_epoch();
    
protected:
    typedef std::vector<double> layer;
    typedef std::vector< std::vector<double> > weights;
    typedef std::vector<double> biases;
    typedef std::vector<double> errors;
    
private:
    size_t input_size;
    std::vector<layer> inner_layers;
    std::vector<weights> matrices;
    std::vector<biases> bias;
    
    double learning_rate;
    
    std::vector<weights> epoch_matrices;
    std::vector<errors> epoch_errors;
    size_t epoch_size;
};

double sigmoid(double x);
double sigmoid_prime(double x);

#endif