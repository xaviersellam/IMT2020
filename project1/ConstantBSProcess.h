#include <iostream>
#include <cmath>
#include <algorithm>
#include <stochasticprocess.hpp>

double gaussian_box_muller();
double norm_cdf(const double& x);
double norm_pdf(const double& x);

namespace QuantLib {

class ConstantBSProcess{ : public StochasticProcess1D {
    private:
double S;
double K;
double r;
double v;
double T;
double q;

    public:
ConstantBSProcess(double S, double K, double r, double v, double T, double q);
path_generator_2(const double& S, const double& K, const double& r, const double& v, const double& T) ;
virtual Real diffusion(Time t, Real x);
virtual Real drift(Time t,Real x);

};
};
}
