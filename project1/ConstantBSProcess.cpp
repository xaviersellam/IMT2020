#include "ConstantBSProcess.h"
#include "blackscholesprocess.hpp"

ConstantBSProcess::ConstantBSProcess(Real S,Rate r,Volatility v,Rate q){
S = 100.0;
r = process_->riskFreeRate()->zeroRate(grid.back(), Continuous);
v = process_->blackVolatility()->blackVol(grid.back(), Continuous);
q = process_->dividendYield()->zeroRate(grid.back(), Continuous);
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
double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));

}

/**double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return S *norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));

}

/**double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
} **/


virtual ConstantBSProcess :: Real drift(Time t,Real x) const{
return((r -0.5*v*v));}

virtual ConstantBSProcess :: Real diffusion(Time t, Real x) const{
//    double k=gaussian_box_muller();
return(v);}

virtual ConstantBSProcess :: Real x0() const{
return(S);}
