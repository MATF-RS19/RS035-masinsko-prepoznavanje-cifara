#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__ 1

#include <vector>
#include <string>

class network{
public:
    network(const std::string& pathname, const std::vector<size_t>& topology, double learning_rate); 
    network(const std::string& pathname, const std::vector<size_t>& topology, double learning_rate, double (*activate) (double), double (*activate_prime) (double));
    network(const std::string& pathname);
    network(const std::string& pathname, double (*activate) (double), double (*activate_prime) (double));
    std::string pathname() const;
    double learning_rate() const;
    size_t input_size() const;
    size_t output_size() const;
    void set_pathname(const std::string& pathname);
    void set_learning_rate(double learning_rate);
    std::vector<double> output() const;
    std::pair<size_t, double> output_pair() const;
    void feed(const std::vector<double>& input);
    void feed(std::vector<double>&& input);
    void track(size_t index);
    void propagate(size_t index); 
    void descend();      
    void reset_statistics();
    double statistics() const;
    double statistics(size_t index) const;
    double epoch_statistics() const;
    double epoch_statistics(size_t index) const;
    void read_state(const std::string& pathname);
    void write_state(const std::string& pathname) const;
    void read_state();
    void write_state() const;
    int result() const;

private:
    class stats{
    public:
        stats();
        explicit stats(size_t output_size);
        void set_size(size_t output_size);
        void add(size_t index, bool correct);
        double calculate() const;
        double calculate(size_t index) const;
        void reset();
    private:
        std::vector<size_t> m_output;
        std::vector<size_t> m_output_counters;
    };
    
    class neuron{
    public:
        neuron(); 
        double value() const;     
        double input() const;
        void set_value(double value);
        void set_input(double input);
        void feed(double input, double (*activate)(double));
        bool operator < (const network::neuron & other) const;
    private:
        double m_value;
        double m_input;
    };
    
protected:
    typedef std::vector<neuron> layer;
    typedef std::vector<std::vector<double> > weight;
    typedef std::vector<double> bias;
    typedef std::vector<double> error; 
    
private:
    std::string m_pathname;
    std::vector<double> m_input_layer;
    std::vector<layer> m_inner_layers;
    std::vector<weight> m_weights;
    std::vector<bias> m_biases;
    std::vector<error> m_errors;

    double m_learning_rate;
    double (*m_activate) (double);     
    double (*m_activate_prime) (double);  

    stats m_statistics;
    
    std::vector<weight> m_epoch_weights;
    std::vector<error> m_epoch_errors;
    size_t m_epoch_size;
    
    stats m_epoch_statistics;
    
    void read(std::ifstream& fin);
    void feed();
    void propagate_back();
    
    template <typename T>
    static T generator(){
        return T();
    }
};

#endif