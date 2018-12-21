#include "network.hpp"
#include <random>

network::network(const std::vector<size_t>& topology, double learning_rate)
: m_input_size(), m_inner_layers(), m_weights(), m_biases(), m_errors(), m_learning_rate(learning_rate), m_epoch_weights(), m_epoch_errors(), m_epoch_size(0)
{
    
    m_input_size = topology[0];
        
    for(size_t i = 1; i<topology.size(); i++){
        m_inner_layers.push_back(layer());
        m_epoch_errors.push_back(error());
        m_errors.push_back(error());
        m_biases.push_back(bias());
        
        for(size_t j=0; j<topology[i]; j++){
            m_inner_layers[i-1].push_back(neuron());
            m_epoch_errors[i-1].push_back(0);
            m_errors[i-1].push_back(0);
            m_biases[i-1].push_back( std::uniform_real_distribution<> (0.0, 1.0) );
        }
    }
    
    m_weights.push_back(weight());
    m_epoch_weights.push_back(weight());
    for(size_t j=0;j<m_inner_layers[0].size(); j++){
        m_weights[0].push_back( std::vector<double>() );
        m_epoch_weights[0].push_back( std::vector<double>() );
        
        for(size_t k=0; k<m_input_size; k++){
            m_weights[0][j].push_back( std::uniform_real_distribution<> (0.0, 1.0) );
            m_epoch_weights[0][j].push_back(0);
        }
    }
    
    for(size_t i=1; i<topology.size()-1; i++){
        m_weights.push_back(weight());
        m_epoch_weights.push_back(weight());

        for(size_t j=0; j<m_inner_layers[i].size(); j++){
            m_weights[i].push_back( std::vector<double>() );
            m_epoch_weights[i].push_back(std::vector<double>());
            
            for(size_t k=0; k<m_inner_layers[i-1]; k++){
                m_weights[i][j].push_back( std::uniform_real_distribution<> (0.0, 1.0) );
                m_epoch_weights[i][j].push_back(0);
            }
        }
    }

}

bool network::feed(const std::vector<double>& input){
	if(input.size()!=m_input_size)
		return false;
	for(size_t i=0; i<m_inner_layers[0].size(); ++i){
		double sum=0;
		for(size_t j=0; j<input[0][i].size(); ++j)
			sum+=m_weights[0][i][j]*input[j];
		m_inner_layers[0][i].feed(sum+m_biases[0][i]);
	}
	for(size_t i=1; i<m_inner_layers.size(); ++i)
		for(size_t j=0; j<m_inner_layers[i].size(); ++j){
			double sum=0;
			for(size_t k=0; k<m_weights[i][j].size(); ++k)
				sum+=m_weights[i][j][k]*m_inner_layers[i-1][k];
			m_inner_layers[i][j].feed(sum+m_biases[i][j];
		}	
	return true;
}

bool network::propagate(const std::vector<double>& output){
	if(output.size()!=m_inner_layers[inner_layers.size()-1].size())
		return false;
	for(size_t i=0, last=m_inner_layers.size()-1; i<m_inner_layers[last].size(); ++i)
		m_errors[last][i]=(m_inner_layers[last][i]-output[i])*
			activate_prime(m_inner_layers[last][i].input());
	propagate_back();
	return true;
}

bool network::propagate(size_t output){
	if(output>=m_inner_layers.size())
		return false;
	for(size_t i=0, last=m_inner_layers.size()-1; i<m_inner_layers[last].size(); ++i)
                m_errors[last][i]=(m_inner_layers[last][i]-output==j)*
                        activate_prime(m_inner_layers[last][i].input());
        propagate_back();
        return true;

}

void network::propagate_back() {
    
    for(size_t curr = m_inner_layers.size()-2; curr >= 0; curr--){
        
        for(size_t i=0; i<m_inner_layers[curr].size(); i++){
            double err=0;
            for(size_t j=0; j<m_weights[i].size(); j++)
                err = err + m_weights[curr][j][i] * m_errors[curr+1][j];
        }
        m_errors[curr][i] = err * activate_prime(m_inner_layers[curr][i].input());
    }

    for(size_t i=0; i<m_epoch_weights.size(); ++i){
        for(size_t j=0; j<m_epoch_weights[i].size(); ++j){
            for(size_t k=0; k<m_epoch_weights[i][j].size(); ++k){
                m_epoch_weights[i][j][k] = m_epoch_weights[i][j][k] + m_errors[i][j] * m_inner_layers[i][k].value();
            }
        }
    }
    
    for(size_t i=0; i<m_epoch_errors.size(); i++){
        for(size_t j=0; j<m_epoch_errors[i].size(); j++){
            // Ovde je m_error[i][j] a ne [i+1][j], zbog nacina na koji cuvamo slojeve i greske (tako da ce nam biti isto indeksirani)
            m_epoch_errors[i][j] = m_epoch_errors[i][j] + m_errors[i][j];
        }
    }
    
    m_epoch_size++;
}

void network::descent() {
        double coeff = m_learning_rate/m_epoch_size;
        
        for(size_t i=0; i<m_weights.size(); ++i){
            for(size_t j=0; j<m_weights[i].size(); ++j){
                for(size_t k=0; k<m_weights[i][j].size(); ++k){
                    m_weights[i][j][k] = m_weights[i][j][k] - coeff*m_epoch_weights[i][j][k];
                    m_epoch_weights[i][j][k]=0;
                }
            }
        }
        
        for(size_t i=0; i<m_biases.size();i++){
            for(size_t j=0; j<m_biases[i].size(); j++){
                m_biases[i][j] = m_biases[i][j] - coeff*m_epoch_errors[i][j];
                m_epoch_errors[i][j]=0;
            }
        }
        
        m_epoch_size = 0;
}

double network::learning_rate() const=0{
    return m_learning_rate;
}

void network::set_learning_rate(double learning_rate) {
     m_learning_rate = learning_rate;
}

network::neuron::neuron()
: m_value(0), m_input(0)
{}

double network::neuron::value() const=0{
        return m_value;
}

double network::neuron::input() const=0{
        return m_input;
}

void network::neuron::feed(double input){
        this->m_input=input;
        value=activate(m_input);
}
