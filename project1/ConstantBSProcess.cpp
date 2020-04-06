#include <ConstantBSProcess.h>

namespace QuantLib {

ConstantBSProcess::ConstantBSProcess(Real S,Rate r,Volatility v,Rate q)
: S(S), r(r), v(v), q(q){}
/**S = 100.0;
r = process_->riskFreeRate()->zeroRate(grid.back(), Continuous);
v = process_->blackVolatility()->blackVol(grid.back(), Continuous);
q = process_->dividendYield()->zeroRate(grid.back(), Continuous);
**/

double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));

}

/**double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return S *norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));

}

/**double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
} **/


Real ConstantBSProcess :: drift(Time t,Real x) const{
return((r-q)*x);
}

Real ConstantBSProcess :: diffusion(Time t, Real x) const{
//    double k=gaussian_box_muller();
return(v*x);
}

Real ConstantBSProcess :: x0() const{
return(S);}

}
