#include "network.hpp"

bool network::feed(const std::vector<double>& input){
	if(input.size()!=input_size)
		return false;
	for(size_t i=0; i<inner_layers[0].size(); ++i){
		double sum=0;
		for(size_t j=0; j<input[0][i].size(); ++j)
			sum+=weight[0][i][j]*input[j];
		inner_layers[0][i].feed(sum+bias[0][i]);
	}
	for(size_t i=1; i<inner_layers.size(); ++i)
		for(size_t j=0; j<inner_layers[i].size(); ++j){
			double sum=0;
			for(size_t k=0; k<weight[i][j].size(); ++k)
				sum+=weight[i][j][k]*inner_layers[i-1][k];
			inner_layers[i][j].feed(sum+bias[i][j];
		}	
	return true;
}

bool network::propogate(const std::vector<double>& output){
	if(output.size()!=inner_layers[inner_layers.size()-1].size())
		return false;
	for(size_t i=0, last=inner_layers.size()-1; i<inner_layers[last].size(); ++i)
		error[last][i]=(inner_layers[last][i]-output[i])*
			activate_prime(inner_layers[last][i].input());
	propogate_back();
	return true;
}

bool network::propogate(size_t output){
	if(output>=inner_layers.size())
		return false;
	for(size_t i=0, last=inner_layers.size()-1; i<inner_layers[last].size(); ++i)
                error[last][i]=(inner_layers[last][i]-output==j)*
                        activate_prime(inner_layers[last][i].input());
        propogate_back();
        return true;

}

network::neuron::value() const=0{
        return value;
}

network::neuron::input() const=0{
        return input;
}

network::neuron::feed(double input){
        this->input=input;
        value=activate(input);
}
