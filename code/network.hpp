#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__ 1

class network{
public:
    network(const std::vector<size_t>& topology, double learning_rate);
    double learning_rate() const=0;
    void set_learning_rate(double learning_rate);
    const std::vector<double>& see_output() const=0;
    bool feed(const std::vector<double>& input);
    bool propogate(const std::vector<double>& output);
    bool propogate(size_t output);
    void descend();
    
protected:
    typedef std::vector<neuron> layer;
    typedef std::vector<std::vector<double> > weights;
    typedef std::vector<double> biases;
    typedef std::vector<double> errors;
    
private:
    size_t input_size;
    std::vector<layer> inner_layers;
    std::vector<weights> weight;
    std::vector<biases> bias;
    std::vector<errors> error;

    double learning_rate;
    double (*activate) (double);
    double (*activate_prime) (double);

    std::vector<weights> epoch_weight;
    std::vector<errors> epoch_error;
    size_t epoch_size;

    void propogate_back();

    class neuron{
    public:
        neuron();
        double value() const=0;
        double input() const=0;
        void feed(double input);

    private:
        double value, input;
    };
};

#endif
