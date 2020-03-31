
#include "constantblackscholesprocess.hpp"
#include "mceuropeanengine.hpp"
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/quantlib.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace QuantLib;


double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));

}

double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return S *norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));

}

double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));

}


int main(int argc, char **argv) {

double S = 100.0;
double K = 100.0;
double r = 0.05;
double v = 0.30;
double T = 1.0;
double q = 0.0;

double call = call_price(S, K, r, v, T);
double put = put_price(S, K, r, v, T);
ConstantBSProcess ConstantBSProcess1;
std::cout<<ConstantBSProcess1.drift()<<std::endl;

return 0;

}
 /*
 int main() {

 try {

        // add your code here

        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
 }

*/
