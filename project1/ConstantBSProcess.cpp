#include <ConstantBSProcess.h>
#include <ql/stochasticprocess.hpp>
#include <ql/termstructures/volatility/equityfx/localvolsurface.hpp>
#include <ql/termstructures/volatility/equityfx/localvolcurve.hpp>
#include <ql/termstructures/volatility/equityfx/localconstantvol.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

using namespace std;

namespace QuantLib {

ConstantBSProcess::ConstantBSProcess(const Handle<Quote> S,const Handle<YieldTermStructure>& r,const Handle<BlackVolTermStructure>& v,const Handle<YieldTermStructure>& q, Date maturity,Real strike,
                boost::shared_ptr<discretization>& d )
                : StochasticProcess1D(d),S(S), r(r), v(v), q(q){
                maturity=maturity;
                strike= ext::dynamic_pointer_cast<StrikedTypePayoff>(this->arguments_.payoff)->strike()
                newr = r->zeroRate(maturity,r-> dayCounter(), Continuous,NoFrequency,true);
                newq = q->zeroRate(maturity,q-> dayCounter(), Continuous,NoFrequency,true);
                newv = v->blackVol(maturity, S->value(),true);
}


/**double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));

}
**/

Real ConstantBSProcess :: drift(Time t,Real x) const{
return((newr-newq)*x);
}

Real ConstantBSProcess :: diffusion(Time t, Real x) const{
//    double k=gaussian_box_muller();
return(newv*x);
}

Real ConstantBSProcess :: x0() const{
return(S->value());}


}
