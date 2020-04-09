#ifndef Constant_BS_Process_h
#define Constant_BS_Process_h

#include <ql/stochasticprocess.hpp>
#include <ql/processes/eulerdiscretization.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/volatility/equityfx/blackvoltermstructure.hpp>
#include <ql/termstructures/volatility/equityfx/localvoltermstructure.hpp>
#include <ql/quote.hpp>

#include <algorithm>
#include <iostream>

namespace QuantLib {

class ConstantBSProcess : public StochasticProcess1D {
    private:
Handle<Quote> S;
Real newr; //r that is calculated in constantBSPorcess.cpp
Real newv;
Real newq;

    public:
ConstantBSProcess(const Handle <Quote> S,const Handle<YieldTermStructure>& r,const Handle<BlackVolTermStructure>& v,const Handle<YieldTermStructure>& q, Date maturity,Real strike,
                  boost::shared_ptr<discretization>& d );

Real diffusion(Time t, Real x) const;
Real drift(Time t,Real x) const;
Real x0() const;

};
}

#endif
