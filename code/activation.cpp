#include "activation.hpp"
#include <math.h>

double sigmoid(double x){
    return 1/(1+std::exp(-x));
}

double sigmoid_prime(double x){
    return (sigmoid(x)-1)/sigmoid(x);
}
