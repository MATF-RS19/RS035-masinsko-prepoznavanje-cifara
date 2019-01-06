#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__ 1

#include <vector>
#include <string>

class network{
public:
    network(const std::string& name, const std::vector<size_t>& topology, double learning_rate); 
    network(const std::string& name, const std::vector<size_t>& topology, double learning_rate, double (*activate) (double), double (*activate_prime) (double));
    network(const std::string& name);
    network(const std::string& name, double (*activate) (double), double (*activate_prime) (double));
    std::string name() const;
    double learning_rate() const;
    size_t input_size() const;
    size_t output_size() const;
    void set_name(const std::string& name);
    void set_learning_rate(double learning_rate);
    std::vector<double> output() const;
    std::pair<size_t, double> output_pair() const;
    void feed(const std::vector<double>& input);
    void feed(std::vector<double>&& input);
    void propagate(size_t index); 
    void descend();      
    void propagate_back();
    void reset_statistics();
    double statistics() const;
    double statistics(size_t index) const;
    double epoch_statistics() const;
    double epoch_statistics(size_t index) const;
    void read_state(const std::string& pathname);
    void write_state(const std::string& pathname) const;
    void read_state();
    void write_state() const;
    
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
    std::string m_name;
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
    
    template <typename T>
    static T generator(){
        return T();
    }
};

#endif
