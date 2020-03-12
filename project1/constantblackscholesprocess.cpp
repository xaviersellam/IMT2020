
#include "constantblackscholesprocess.hpp"

ConstantBSProcess::ConstantBSProcess(){
double S = 100.0;
double K = 100.0;
double r = 0.05;
double v = 0.30;
double T = 1.0;
double q =0.0;
}


double norm_pdf(const double& x) {
return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);

}

double norm_cdf(const double& x) {
double k = 1.0/(1.0 + 0.2316419*x);
double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

if (x >= 0.0) {
return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);

} else {
return 1.0 - norm_cdf(-x);

}
}

double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;
// A simple implementation of the Box-Muller algorithm, used to generate
// gaussian random numbers - necessary for the Monte Carlo method below
  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}


double ConstantBSProcess :: drift(){
std::cout<<r<<std::endl;
return((r -0.5*v*v)*T);}

double ConstantBSProcess :: diffusion(){
    double k=gaussian_box_muller();
return(v*pow(T,0.5)*k);}

