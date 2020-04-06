
#include <ConstantBSProcess.h>
#include <mceuropeanengine.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/quantlib.hpp>
#include <mcvanillaengine.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/stochasticprocess.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace QuantLib;


/**double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));

}

double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return S *norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));

}

double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));

}

**/
int main() {
     try {
//        std::chrono::time_point<std::chrono::system_clock> start, end;
//    	start = std::chrono::steady_clock::now();

        // set up dates
        Calendar calendar = TARGET();
        Date todaysDate(20, September, 1997);
        Date settlementDate(22, September, 1997);
        Settings::instance().evaluationDate() = todaysDate;

        // our options
        Option::Type type(Option::Put);
        Real S = 20;
        Real strike = 30;
        Rate q = 0.00;
        Rate r = 0.05;
        Volatility v = 0.15;
        Date maturity(22, September, 1998);
        DayCounter dayCounter = Actual365Fixed();

        std::vector<Date> exerciseDates;
        for (Integer i=1; i<=4; i++)
            exerciseDates.push_back(settlementDate + 3*i*Months);

        Handle<Quote> x0(
            boost::shared_ptr<Quote>(new SimpleQuote(S)));

        Handle<YieldTermStructure> riskFreeTS(
            boost::shared_ptr<YieldTermStructure>(
                new FlatForward(settlementDate, r, dayCounter)));
        Handle<YieldTermStructure> dividendTS(
            boost::shared_ptr<YieldTermStructure>(
                new FlatForward(settlementDate, q, dayCounter)));
        Handle<BlackVolTermStructure> blackVolTS(
            boost::shared_ptr<BlackVolTermStructure>(
                new BlackConstantVol(settlementDate, calendar, v,
                                     dayCounter)));

        boost::shared_ptr<GeneralizedBlackScholesProcess> bsProcess(
                 new GeneralizedBlackScholesProcess(x0, dividendTS,
                                               riskFreeTS, blackVolTS));
        //Pricing of a Vanilla Option
        boost::shared_ptr<StrikedTypePayoff> payoff(
                                        new PlainVanillaPayoff(type, strike));
        boost::shared_ptr<Exercise> europeanExercise(
                                         new EuropeanExercise(maturity));
        VanillaOption europeanOption(payoff, europeanExercise);

        // Monte Carlo Method:
        int timeSteps = 20;
        Size mcSeed = 42;

	// Using the MCEuropeanEngine_2 from mceuropeanengine.hpp
        boost::shared_ptr<PricingEngine> mcengine;
        mcengine = MakeMCEuropeanEngine_2<PseudoRandom>(bsProcess)
            .withSteps(timeSteps)
            .withAbsoluteTolerance(0.02)
            .withSeed(mcSeed)
            .withconstantparameters(true);
        europeanOption.setPricingEngine(mcengine);

	// Total elapsed time
//	end = std::chrono::steady_clock::now();
//		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
//		<< " ms" << std::endl;
return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
 }

