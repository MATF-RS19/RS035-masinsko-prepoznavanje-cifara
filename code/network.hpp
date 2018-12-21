#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__ 1

class network{
public:
    network(const std::vector<size_t>& topology, double learning_rate);  
    double learning_rate() const=0; 
    void set_learning_rate(double learning_rate); 
    const std::vector<double>& see_output() const=0; 
    bool feed(const std::vector<double>& input);  
    bool propagate(const std::vector<double>& output); 
    bool propagate(size_t output); 
    void descend();      
    void propagate_back();   

protected:
    typedef std::vector<neuron> layer;
    typedef std::vector<std::vector<double> > weight;
    typedef std::vector<double> bias;
    typedef std::vector<double> error;
    
private:
    size_t m_input_size;
    std::vector<layer> m_inner_layers;
    std::vector<weight> m_weights;
    std::vector<bias> m_biases;
    std::vector<error> m_errors;

    double m_learning_rate;
    double (*activate) (double);     
    double (*activate_prime) (double);  

    std::vector<weight> m_epoch_weights;
    std::vector<error> m_epoch_errors;
    size_t m_epoch_size;

    class neuron{
    public:
        neuron(); 
        double value() const=0;     
        double input() const=0;     
        void feed(double input); 

    private:
        double m_value;
        double m_input;
    };
};

#endif
