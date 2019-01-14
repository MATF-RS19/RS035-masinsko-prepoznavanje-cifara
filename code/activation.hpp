#ifndef __ACTIVATION_HPP___
#define __ACTIVATION_HPP___ 1

double sigmoid(double x);

double sigmoid_prime(double x);

double identity(double x);

double identity_prime(double x);

double tan_h(double x);

double tan_h_prime(double x);

double arc_tan(double x);

double arc_tan_prime(double x);

double eliot_sig(double x);

double eliot_sig_prime(double x);

double square_nonlinearity(double x);

double square_nonlinearity_prime(double x);

double gaussian(double x);

double gaussian_prime(double x);

double soft_plus(double x);

double soft_plus_prime(double x);

double restricted_linear_unit(double x);

double restricted_linear_unit_prime(double x);

#endif 