
#include <ql/stochasticprocess.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace QuantLib {

double gaussian_box_muller();
double norm_cdf(const double& x);
double norm_pdf(const double& x);

    class ConstantBSProcess {//: public StochasticProcess1D {

    private:
double S;
double K;
double r;
double v;
double T;
double q;

    public:
ConstantBSProcess();
double diffusion();
double drift();

};

    };

}

