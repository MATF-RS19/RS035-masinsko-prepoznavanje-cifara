#include "network.hpp"
#include "activation.hpp"

#include <algorithm>
#include <iterator>
#include <random>
#include <numeric>
#include <utility>

network::network(const string& name, const std::vector<size_t>& topology, double learning_rate)
:m_name(name), m_output_size(topology.back()), m_input_layer(topology.front()), m_inner_layers(topology.size()-1, layer()), m_weights(topology.size()-1, weight()),
 m_biases(topology.size()-1, bias()), m_errors(topology.size()-1, error()), m_learning_rate(learning_rate), m_activate(sigmoid), m_activate_prime(sigmoid_prime), 
 m_statistics(topology.back()), m_epoch_weights(topology.size()-1, weight()), m_epoch_errors(topology.size()-1, error()), m_epoch_size(0), m_epoch_statistics(topology.back())
{  
    for(size_t i = 1; i<topology.size(); ++i){
        std::fill_n(std::back_inserter(m_inner_layers[i-1]), topology[i], neuron());
        std::fill_n(std::back_inserter(m_biases[i-1]), topology[i], std::uniform_real_distribution(0.0, 1.0));
        std::fill_n(std::back_inserter(m_errors[i-1]), topology[i], 0.0);
        std::fill_n(std::back_inserter(m_epoch_errors[i-1]), topology[i], 0.0);
        
        std::fill_n(std::back_inserter(m_weights[i-1]), topology[i], std::vector<double>());
        std::fill_n(std::back_inserter(m_epoch_weights[i-1]), topology[i], std::vector<double>());
        for(size_t j=0; j<topology[i]; ++j){
            std::fill_n(std::back_inserter(m_weights[i-1][j]), topology[i-1], std::uniform_real_distribution(0.0, 1.0));
            std::fill_n(std::back_inserter(m_epoch_weights[i-1][j]), topology[i-1], 0.0);
        }
    }
}

network::network(const string& name, const std::vector<size_t>& topology, double learning_rate, double (*activate)(double), double (*activate_prime)(double))
:m_name(name), m_output_size(topology.back()), m_input_layer(topology.front()), m_inner_layers(topology.size()-1, layer()), m_weights(topology.size()-1, weight()),
 m_biases(topology.size()-1, bias()), m_errors(topology.size()-1, error()), m_learning_rate(learning_rate), m_activate(activate), m_activate_prime(activate_prime), 
 m_statistics(topology.back()), m_epoch_weights(topology.size()-1, weight()), m_epoch_errors(topology.size()-1, error()), m_epoch_size(0), m_epoch_statistics(topology.back())
{  
    for(size_t i = 1; i<topology.size(); ++i){
        std::fill_n(std::back_inserter(m_inner_layers[i-1]), topology[i], neuron());
        std::fill_n(std::back_inserter(m_biases[i-1]), topology[i], std::uniform_real_distribution(0.0, 1.0));
        std::fill_n(std::back_inserter(m_errors[i-1]), topology[i], 0.0);
        std::fill_n(std::back_inserter(m_epoch_errors[i-1]), topology[i], 0.0);
        
        std::fill_n(std::back_inserter(m_weights[i-1]), topology[i], std::vector<double>());
        std::fill_n(std::back_inserter(m_epoch_weights[i-1]), topology[i], std::vector<double>());
        for(size_t j=0; j<topology[i]; ++j){
            std::fill_n(std::back_inserter(m_weights[i-1][j]), topology[i-1], std::uniform_real_distribution(0.0, 1.0));
            std::fill_n(std::back_inserter(m_epoch_weights[i-1][j]), topology[i-1], 0.0);
        }
    }
}

std::string network::name() const{
    return m_name;
}

void network::set_name(const std::string& name){
    m_name=name;
}

double network::learning_rate() const{
    return m_learning_rate;
}

void network::set_learning_rate(double learning_rate){
     m_learning_rate = learning_rate;
}

size_t network::input_size() const{
    return m_input_layer.size();
}

size_t network::output_size() const{
    return m_inner_layers.back().size();
}

std::vector<double> network::output() const{
    return m_inner_layers.back();
}

std::pair<size_t, double> network::output_pair() const{
    auto max_iter=std::max_element(m_inner_layers.back().cbegin(), m_inner_layers.back().cend(), [](const neuron& a, const neuron& b){return a.value()<b.value();});
    return std::make_pair(max_iter-m_inner_layers.back().cbegin(), max_iter->value());
}

void network::feed(const std::vector<double>& input){
    std::copy(input.cbegin(), input.cend(), m_input_layer.begin());
    for(size_t i=0; i<m_inner_layers[0].size(); ++i)
        m_inner_layers[0][i].feed(m_biases[0][i]+std::inner_product(m_weights[0][i].cbegin(), m_weights[0][i].cend(), m_input_layer.cbegin(), 0.0));
	for(size_t i=1; i<m_inner_layers.size(); ++i)
		for(size_t j=0; j<m_inner_layers[i].size(); ++j)
            m_inner_layers[i][j].feed(m_biases[i][j]+std::inner_product(m_weights[i][j].cbegin(), m_weights[i][j].cend(), m_inner_layers[i-1].cbegin(), 0.0, [](double a, double b){return a+b;}, [](double a,const neuron& b){return a*b.value()}));		
}

void network::feed(std::vector<double>&& input){
    m_input_layer=std::move(input);
    for(size_t i=0; i<m_inner_layers[0].size(); ++i)
        m_inner_layers[0][i].feed(m_biases[0][i]+std::inner_product(m_weights[0][i].cbegin(), m_weights[0][i].cend(), m_input_layer.cbegin(), 0.0));
	for(size_t i=1; i<m_inner_layers.size(); ++i)
		for(size_t j=0; j<m_inner_layers[i].size(); ++j)
            m_inner_layers[i][j].feed(m_biases[i][j]+std::inner_product(m_weights[i][j].cbegin(), m_weights[i][j].cend(), m_inner_layers[i-1].cbegin(), 0.0, [](double a, double b){return a+b;}, [](double a,const neuron& b){return a*b.value()}));			
}

void network::propagate(size_t index){
    bool flag = output_pair().first==index;
    m_statistics.add(index, flag);
    m_epoch_statistics.add(index, flag);
	for(size_t i=0; i<m_inner_layers.back().size(); ++i){
        m_errors.back()[i]=(m_inner_layers.back()[i]-index==i)*m_activate_prime(m_inner_layers.back()[i].input());
        m_epoch_errors.back()[i]+=m_errors.back()[i];
    }
    propagate_back();
}

void network::propagate_back() {
    for(size_t curr = m_errors.size()-2; curr > 0; --curr)
        for(size_t i=0; i<m_errors[curr].size(); ++i){
            double err=0.0;
            for(size_t j=0; j<m_weights[curr+1].size(); ++j)
                err += m_weights[curr+1][j][i] * m_errors[curr+1][j];
            m_errors[curr][i] = err * m_activate_prime(m_inner_layers[curr][i].input());
        }
        
    for(size_t i=0; i<m_errors[0].size(); ++i){
        double err=0.0;
        for(size_t j=0; j<m_weights[1].size(); ++j)
            err+= m_weights[1][j][i] * m_errors[1][j];
        m_errors[1][i]=err * m_activate_prime(m_input_layer[i].input());
    }
    
    /*
    for(size_t i=0; i<m_epoch_weights[0].size(); ++i)
        for(size_t j=0; j<m_epoch_weights[0][j].size(); ++j)
            m_epoch_weights[0][i][j]+=m_errors[0][i]*m_input_layer[j];
        
    for(size_t i=1; i<m_epoch_weights.size(); ++i)
        for(size_t j=0; j<m_epoch_weights[i].size(); ++j)
            for(size_t k=0; k<m_epoch_weights[i][j].size(); ++k)
                m_epoch_weights[i][j][k]+=m_errors[i][j]*m_inner_layers[i-1][k];
     */
    
    for(size_t i=0; i<m_epoch_weights[0].size(); ++i)
        std::transform(m_epoch_weights[0][i].cbegin(), m_epoch_weights[0][i].cend(), m_input_layer.cbegin(), m_epoch_weights[0][i].begin(), [m_errors[0][i]](double a, double b){return a+m_errors[0][i]*b;});
            
    for(size_t i=1; i<m_epoch_weights.size(); ++i)
        for(size_t j=0; j<m_epoch_weights[i].size(); ++j)
            std::transform(m_epoch_weights[i][j].cbegin(), m_epoch_weights[i][j].cend(), m_inner_layers[i-1].cbegin(), m_epoch_weights[i][j].begin(), 
                           [m_errors[i][j]](double a,double b){return a+m_errors[i][j]*b;});
    
    /*
    for(size_t i=0; i<m_epoch_errors.size(); ++i)
        for(size_t j=0; j<m_epoch_errors[i].size(); ++j)
            m_epoch_errors[i][j]+=m_errors[i][j];
    */
            
    for(size_t i=0; i<m_epoch_errors.size(); ++i)
        std::transform(m_epoch_errors[i].cbegin(), m_epoch_errors[i].cend(), m_errors[i].cbegin(), m_epoch_errors[i].begin(), [](double a, double b){return a+b;});
    ++m_epoch_size;
}

void network::descend(){
        double coeff = m_learning_rate/m_epoch_size;
        
        /* 
        for(size_t i=0; i<m_weights.size(); ++i)
            for(size_t j=0; j<m_weights[i].size(); ++j)
                for(size_t k=0; k<m_weights[i][j].size(); ++k){
                    m_weights[i][j][k]-=coeff*m_epoch_weights[i][j][k];
                    m_epoch_weights[i][j][k]=0.0;
                }
        */
        
        for(size_t i=0; i<m_weights.size(); ++i)
            for(size_t j=0; j<m_weights[i].size(); ++j){
                std::transform(m_weights[i][j].cbegin(), m_weights[i][j].cend(), m_epoch_weights[i][j].cbegin(), m_weights[i][j].begin(), [coeff](double a, double b){return a-coeff*b;});
                std::fill(m_epoch_weights[i][j].begin(), m_epoch_weights[i][j].end(), 0.0);
            }
            
        /*
        for(size_t i=0; i<m_biases.size(); ++i)
            for(size_t j=0; j<m_biases[i].size(); ++j){
                m_biases[i][j]-=coeff*m_epoch_errors[i][j];
                m_epoch_errors[i][j]=0.0;
        */
        
        for(size_t i=0; i<m_biases.size(); ++i){
            std::transform(m_biases[i].cbegin(), m_biases[i].cend(), m_epoch_errors[i].cbegin(), m_biases[i].begin(), [coeff](double a, double b){return a-coeff*b;});
            std::fill(m_epoch_errors[i].begin(), m_epoch_errors[i][j].end(), 0.0);
        }
        
        m_epoch_size = 0;
        m_epoch_statistics.reset();
}

void network::reset_statistics(){
    m_statistics.reset();
    m_epoch_statistics.reset();
}

double network::statistics() const{
    return m_statistics.calculate();
}

double network::statistics(size_t index) const{
    return m_statistics.calculate(index);
}
  
double network::epoch_statistics() const{
    return m_epoch_statistics.calculate();
}

double network::epoch_statistics(size_t index) const{
    return m_epoch_statistics.calculate(index);
}

void network::read_state(const std::string& pathname=m_name+".network"){}

void network::write_state(const std::string& pathname=m_name+".network") const{}

explicit network::statistics::statistics(size_t output_size):m_output(output_size, 0), m_output_counters(output_size, 0){}

void network::statistics::add(size_t index, bool correct){
    m_output[index]+=correct;
    ++m_output_counters[index];
}

double network::statistics::calculate() const{
    return double(std::accumulate(m_output.cbegin(), m_output.cend(), 0))/std::accumulate(m_output_counters.cbegin(), m_output_counters.cend(), 0);
}

double network::statistics::calculate(size_t index) const{
    return double(m_output[index])/m_output_counters[index];
}

void network::statistics::reset(){
    std::fill(m_output.begin(), m_output.end(), 0);
    std::fill(m_output_counters.begin(), m_output_counters.end(), 0);
}

network::neuron::neuron()
: m_value(0.0), m_input(0.0)
{}

double network::neuron::value() const{
        return m_value;
}

double network::neuron::input() const{
        return m_input;
}

void network::neuron::feed(double input){
        m_input=input;
        m_value=m_activate(m_input);
}
