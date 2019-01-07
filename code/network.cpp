#include "network.hpp"
#include "activation.hpp"

#include <algorithm>
#include <iterator>
#include <random>
#include <numeric>
#include <utility>
#include <fstream>

#include <iostream>

network::network(const std::string& pathname, const std::vector<size_t>& topology, double learning_rate):network(pathname, topology, learning_rate, sigmoid, sigmoid_prime){}

network::network(const std::string& pathname, const std::vector<size_t>& topology, double learning_rate, double (*activate)(double), double (*activate_prime)(double)):
    m_pathname(pathname), m_input_layer(topology.front()), m_inner_layers(topology.size()-1, layer()), m_weights(topology.size()-1, weight()), m_biases(topology.size()-1, bias()), m_errors(topology.size()-1, error()), m_learning_rate(learning_rate), m_activate(activate), m_activate_prime(activate_prime), m_statistics(topology.back()), m_epoch_weights(topology.size()-1, weight()), m_epoch_errors(topology.size()-1, error()), m_epoch_size(0), m_epoch_statistics(topology.back())
{  
    std::default_random_engine bias_generator, weight_generator;
    std::uniform_real_distribution<double> bias_distribution(0.0, 1.0), weight_distribution(0.0, 1.0);
    for(size_t i = 1; i<topology.size(); ++i){
        m_inner_layers[i-1].reserve(topology[i]);
        m_biases[i-1].reserve(topology[i]);
        m_errors[i-1].reserve(topology[i]);
        m_epoch_errors[i-1].reserve(topology[i]);
        m_weights[i-1].reserve(topology[i]);
        m_epoch_weights[i-1].reserve(topology[i]);
        
        std::generate_n(std::back_inserter(m_inner_layers[i-1]), topology[i], generator<neuron>);
        std::generate_n(std::back_inserter(m_biases[i-1]), topology[i], [&bias_generator, &bias_distribution]() mutable {return bias_distribution(bias_generator);});
        std::fill_n(std::back_inserter(m_errors[i-1]), topology[i], 0.0);
        std::fill_n(std::back_inserter(m_epoch_errors[i-1]), topology[i], 0.0);
        
        std::generate_n(std::back_inserter(m_weights[i-1]), topology[i], generator<std::vector<double> >);
        std::generate_n(std::back_inserter(m_epoch_weights[i-1]), topology[i], generator<std::vector<double> >);
        for(size_t j=0; j<topology[i]; ++j){
            m_weights[i-1][j].reserve(topology[i-1]);
            m_epoch_weights[i-1][j].reserve(topology[i-1]);
            
            std::generate_n(std::back_inserter(m_weights[i-1][j]), topology[i-1], 
                [&weight_generator, &weight_distribution]() mutable {return weight_distribution(weight_generator);});
            std::fill_n(std::back_inserter(m_epoch_weights[i-1][j]), topology[i-1], 0.0);
        }
    }
}

network::network(const std::string& pathname):network(pathname, sigmoid, sigmoid_prime){}

network::network(const std::string& pathname, double (*activate) (double), double (*activate_prime) (double)):
    m_pathname(pathname), m_activate(activate), m_activate_prime(activate_prime), m_epoch_size(0)
{
    std::ifstream fin(pathname, std::ios::in);
    size_t topology_size;
    fin>>topology_size;
    
    m_inner_layers.reserve(topology_size-1);
    m_weights.reserve(topology_size-1);
    m_biases.reserve(topology_size-1);
    m_errors.reserve(topology_size-1);
    m_epoch_errors.reserve(topology_size-1);
    m_epoch_weights.reserve(topology_size-1);
    
    std::generate_n(std::back_inserter(m_inner_layers), topology_size-1, generator<layer>);
    std::generate_n(std::back_inserter(m_weights), topology_size-1, generator<weight>);
    std::generate_n(std::back_inserter(m_biases), topology_size-1, generator<bias>);
    std::generate_n(std::back_inserter(m_errors), topology_size-1, generator<error>);
    std::generate_n(std::back_inserter(m_epoch_weights), topology_size-1, generator<weight>);
    std::generate_n(std::back_inserter(m_epoch_errors), topology_size-1, generator<error>);
    
    std::vector<size_t> topology;
    std::copy_n(std::istream_iterator<size_t>(fin), topology_size, std::back_inserter(topology));
    
    m_input_layer.reserve(topology.front());
    std::fill_n(std::back_inserter(m_input_layer), topology.front(), 0.0);
    m_statistics.set_size(topology.back());
    m_epoch_statistics.set_size(topology.back());

    for(size_t i = 1; i<topology_size; ++i){
        m_inner_layers[i-1].reserve(topology[i]);
        m_biases[i-1].reserve(topology[i]);
        m_errors[i-1].reserve(topology[i]);
        m_epoch_errors[i-1].reserve(topology[i]);
        m_weights[i-1].reserve(topology[i]);
        m_epoch_weights[i-1].reserve(topology[i]);
        
        std::generate_n(std::back_inserter(m_inner_layers[i-1]), topology[i], generator<neuron>);
        std::fill_n(std::back_inserter(m_biases[i-1]), topology[i], 0.0);
        std::fill_n(std::back_inserter(m_errors[i-1]), topology[i], 0.0);
        std::fill_n(std::back_inserter(m_epoch_errors[i-1]), topology[i], 0.0);
        
        std::generate_n(std::back_inserter(m_weights[i-1]), topology[i], generator<std::vector<double> >);
        std::generate_n(std::back_inserter(m_epoch_weights[i-1]), topology[i], generator<std::vector<double> >);
        for(size_t j=0; j<topology[i]; ++j){
            m_weights[i-1][j].reserve(topology[i-1]);
            m_epoch_weights[i-1][j].reserve(topology[i-1]);
            
            std::fill_n(std::back_inserter(m_weights[i-1][j]), topology[i-1], 0.0);
            std::fill_n(std::back_inserter(m_epoch_weights[i-1][j]), topology[i-1], 0.0);
        }
    }
    
    read(fin);
}

std::string network::pathname() const{
    return m_pathname;
}

double network::learning_rate() const{
    return m_learning_rate;
}

size_t network::input_size() const{
    return m_input_layer.size();
}

size_t network::output_size() const{
    return m_inner_layers.back().size();
}

void network::set_pathname(const std::string& pathname){
    m_pathname=pathname;
}

void network::set_learning_rate(double learning_rate){
     m_learning_rate = learning_rate;
}

std::vector<double> network::output() const{
    std::vector<double> result(m_inner_layers.back().size());
    std::transform(m_inner_layers.back().cbegin(), m_inner_layers.back().cend(), result.begin(), [](const neuron& n){return n.value();});
    return result;
}

std::pair<size_t, double> network::output_pair() const{
    auto max_iter=std::max_element(m_inner_layers.back().cbegin(), m_inner_layers.back().cend(), [](const neuron& a, const neuron& b){return a.value()<b.value();});
    return std::make_pair(max_iter-m_inner_layers.back().cbegin(), max_iter->value());
}

void network::feed(const std::vector<double>& input){
    std::copy(input.cbegin(), input.cend(), m_input_layer.begin());
    feed();		
}

void network::feed(std::vector<double>&& input){
    m_input_layer=std::move(input);
    feed();		
}

void network::track(size_t index){
    bool flag = output_pair().first==index;
    m_statistics.add(index, flag);
    m_epoch_statistics.add(index, flag);
}

void network::propagate(size_t index){
	for(size_t i=0; i<m_inner_layers.back().size(); ++i)
        m_errors.back()[i]=(m_inner_layers.back()[i].value()-index==i)*m_activate_prime(m_inner_layers.back()[i].input());
    propagate_back();
}

void network::descend(){
        double coeff = m_learning_rate/m_epoch_size;
        
        for(size_t i=0; i<m_weights.size(); ++i)
            for(size_t j=0; j<m_weights[i].size(); ++j){
                std::transform(m_weights[i][j].cbegin(), m_weights[i][j].cend(), m_epoch_weights[i][j].cbegin(), m_weights[i][j].begin(), [coeff](double a, double b){return a-coeff*b;});
                std::fill(m_epoch_weights[i][j].begin(), m_epoch_weights[i][j].end(), 0.0);
            }
            
        
        for(size_t i=0; i<m_biases.size(); ++i){
            std::transform(m_biases[i].cbegin(), m_biases[i].cend(), m_epoch_errors[i].cbegin(), m_biases[i].begin(), [coeff](double a, double b){return a-coeff*b;});
            std::fill(m_epoch_errors[i].begin(), m_epoch_errors[i].end(), 0.0);
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

void network::read_state(const std::string& pathname){
    std::ifstream fin(pathname, std::ios::in);
    {
        size_t tmp_size;
        fin>>tmp_size;
        std::vector<size_t> tmp_v;
        std::copy_n(std::istream_iterator<size_t>(fin), tmp_size, std::back_inserter(tmp_v));
    }
    read(fin);
}

void network::write_state(const std::string& pathname) const{
    std::ofstream fout(pathname, std::ios::out);
    fout<<1+m_inner_layers.size()<<std::endl;
    fout<<m_input_layer.size()<<" ";
    std::transform(m_inner_layers.cbegin(), m_inner_layers.cend(), std::ostream_iterator<size_t>(fout, " "), [](const layer& l){return l.size();});
    fout<<std::endl;
    std::copy(m_input_layer.cbegin(), m_input_layer.cend(), std::ostream_iterator<double>(fout, " "));
    for(const layer& l: m_inner_layers)
        for(const neuron& n: l)
            fout<<" "<<n.input()<<" "<<n.value();
    fout<<std::endl;
    for(const weight& w: m_weights)
        for(const std::vector<double>& v: w)
            std::copy(v.cbegin(), v.cend(), std::ostream_iterator<double>(fout, " "));
    fout<<std::endl;
    for(const bias& b: m_biases)
        std::copy(b.cbegin(), b.cend(), std::ostream_iterator<double>(fout, " "));
    fout<<std::endl;
    for(const error& e: m_errors)
        std::copy(e.cbegin(), e.cend(), std::ostream_iterator<double>(fout, " "));
    fout<<std::endl;
    fout<<m_learning_rate;
}

void network::read_state(){
    read_state(m_pathname);
}

void network::write_state() const{
    write_state(m_pathname);
}

network::stats::stats(){}

network::stats::stats(size_t output_size):m_output(output_size, 0), m_output_counters(output_size, 0){}

void network::stats::add(size_t index, bool correct){
    m_output[index]+=correct;
    ++m_output_counters[index];
}

void network::stats::set_size(size_t output_size){
    std::fill_n(back_inserter(m_output), output_size, 0);
    std::fill_n(back_inserter(m_output_counters), output_size, 0);
}

double network::stats::calculate() const{
    return double(std::accumulate(m_output.cbegin(), m_output.cend(), 0))/std::accumulate(m_output_counters.cbegin(), m_output_counters.cend(), 0);
}

double network::stats::calculate(size_t index) const{
    return double(m_output[index])/m_output_counters[index];
}

void network::stats::reset(){
    std::fill(m_output.begin(), m_output.end(), 0);
    std::fill(m_output_counters.begin(), m_output_counters.end(), 0);
}

network::neuron::neuron(): m_value(0.0), m_input(0.0)
{}

double network::neuron::value() const{
        return m_value;
}

double network::neuron::input() const{
        return m_input;
}

void network::neuron::set_value(double value){
    m_value=value;
}

void network::neuron::set_input(double input){
    m_input=input;
}

void network::neuron::feed(double input, double (*activate)(double)){
        m_input=input;
        m_value=activate(m_input);
}

void network::read(std::ifstream& fin){
    std::copy_n(std::istream_iterator<double>(fin), m_input_layer.size(), m_input_layer.begin());
    for(layer& l: m_inner_layers)
        for(neuron& n: l){
            double tmp;
            fin>>tmp;
            n.set_input(tmp);
            fin>>tmp;
            n.set_value(tmp);
        }
    for(weight& w: m_weights)
        for(std::vector<double>& v: w)
            std::copy_n(std::istream_iterator<double>(fin), v.size(), v.begin());
    for(bias& b: m_biases)
        std::copy_n(std::istream_iterator<double>(fin), b.size(), b.begin());
    for(error& e: m_errors)
        std::copy_n(std::istream_iterator<double>(fin), e.size(), e.begin());
    fin>>m_learning_rate;
}

void network::feed(){
    for(size_t i=0; i<m_inner_layers[0].size(); ++i)
        m_inner_layers[0][i].feed(m_biases[0][i]+std::inner_product(m_weights[0][i].cbegin(), m_weights[0][i].cend(), m_input_layer.cbegin(), 0.0), m_activate);
    for(size_t i=1; i<m_inner_layers.size(); ++i)
        for(size_t j=0; j<m_inner_layers[i].size(); ++j)
            m_inner_layers[i][j].feed(m_biases[i][j]+std::inner_product(m_weights[i][j].cbegin(), m_weights[i][j].cend(), m_inner_layers[i-1].cbegin(), 0.0, [](double a, double b){return a+b;}, [](double a, const neuron& b){return a*b.value();}), m_activate);
}

void network::propagate_back(){
    for(size_t curr = m_errors.size()-1; curr > 0; --curr)
        for(size_t i=0; i<m_errors[curr-1].size(); ++i){
            double err=0.0;
            for(size_t j=0; j<m_weights[curr].size(); ++j)
                err += m_weights[curr][j][i] * m_errors[curr][j];
            m_errors[curr-1][i] = err * m_activate_prime(m_inner_layers[curr-1][i].input());
        }

    for(size_t i=0; i<m_epoch_weights[0].size(); ++i){
        double tmp=m_errors[0][i];
        std::transform(m_epoch_weights[0][i].cbegin(), m_epoch_weights[0][i].cend(), m_input_layer.cbegin(), m_epoch_weights[0][i].begin(), [tmp](double a, double b){return a+tmp*b;});
    }
    
    for(size_t i=1; i<m_epoch_weights.size(); ++i)
        for(size_t j=0; j<m_epoch_weights[i].size(); ++j){
            double tmp=m_errors[i][j];
            std::transform(m_epoch_weights[i][j].cbegin(), m_epoch_weights[i][j].cend(), m_inner_layers[i-1].cbegin(), m_epoch_weights[i][j].begin(), 
                           [tmp](double a, const neuron& b){return a+tmp*b.value();});
        }
            
    for(size_t i=0; i<m_epoch_errors.size(); ++i)
        std::transform(m_epoch_errors[i].cbegin(), m_epoch_errors[i].cend(), m_errors[i].cbegin(), m_epoch_errors[i].begin(), [](double a, double b){return a+b;});
    ++m_epoch_size;
}
