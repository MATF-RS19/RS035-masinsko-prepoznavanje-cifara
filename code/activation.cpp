#include "activation.hpp"
#include <math.h>
#include <cmath>
#include <ctgmath>

double sigmoid(double x){
    return 1/(1+std::exp(-x));
}

double sigmoid_prime(double x){
    return (sigmoid(x)-1)/sigmoid(x);
}

double identity(double x){
    return x;
}

double identity_prime(double x){
    return 1;
}

double tan_h(double x){
    return (std::exp(x)-std::exp(-x))/(std::exp(x)+std::exp(-x));
}

double tan_h_prime(double x){
    return 1-pow(tan_h(x), 2);
}

double arc_tan(double x){
    return atan(x);
}

double arc_tan_prime(double x){
    return 1/(pow(x,2)+1);
}

double eliot_sig(double x){
    return x/(1+abs(x));
}

double eliot_sig_prime(double x){
    return 1/pow(1+abs(x), 2);
}

double square_nonlinearity(double x){
    if(x>2.0)
        return 1;
    else if(x>=0 && x<=2)
        return x-pow(x, 2)/4;
    else if(x>=-2.0 && x<0)
        return x+pow(x, 2)/4;
    else 
        return -1;
}

double square_nonlinearity_prime(double x){
    return 1+x/2;
}
    
double gaussian(double x){
    return std::exp(-pow(x,2));
}

double gaussian_prime(double x){
    return -2*x*std::exp(-pow(x,2));
}

double soft_plus(double x){
    return log(1+std::exp(x));
}

double soft_plus_prime(double x){
    return 1/(1+std::exp(-x));
}

double restricted_linear_unit(double x){
    if(x<0)
        return 0;
    return x;
}

double restricted_linear_unit_prime(double x){
    if(x<0)
        return 0;
    else
        return 1;
}