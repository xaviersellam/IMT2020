#include <iostream>
#include <cmath>
#include <algorithm>
#include <stochasticprocess.hpp>

double gaussian_box_muller();
double norm_cdf(const double& x);
double norm_pdf(const double& x);

namespace QuantLib {

class ConstantBSProcess : public StochasticProcess1D {
    private:
Real S;
Rate r;
Volatility v;
Rate q;

    public:
ConstantBSProcess(Real S,Rate r,Volatility v,Rate q);
virtual Real diffusion(Time t, Real x) const;
virtual Real drift(Time t,Real x) const;
virtual Real x0() const;

};
};
}
