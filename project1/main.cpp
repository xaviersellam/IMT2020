#include <ConstantBSProcess.h>
#include <mceuropeanengine.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/quantlib.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <time.h>
#include <iostream>

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
        Date maturity(20, September, 2019);
        Date settlementDate(20, September, 2018);
        DayCounter dayCounter = Actual365Fixed();

        // our options
        Real S = 90;
        Real strike = 100;
        Rate q = 0.00;
        Rate r = 0.05;
        Volatility v = 0.15;
        Option::Type type(Option::Call);

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

        boost::shared_ptr<GeneralizedBlackScholesProcess> bsProcess = boost::shared_ptr<GeneralizedBlackScholesProcess>(
                 new GeneralizedBlackScholesProcess(x0, dividendTS,
                                               riskFreeTS, blackVolTS));
        //Pricing of a Vanilla Option
        boost::shared_ptr<StrikedTypePayoff> payoff(
                                        new PlainVanillaPayoff(type, strike));
        boost::shared_ptr<Exercise> europeanExercise(
                                         new EuropeanExercise(maturity));

        VanillaOption europeanOption(payoff, europeanExercise);
        VanillaOption europeanOption_2(payoff, europeanExercise);

//set option
		europeanOption.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new AnalyticEuropeanEngine(bsProcess)
				));
		europeanOption_2.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new AnalyticEuropeanEngine(bsProcess)
				));
		std::cout << "--------------------------------------------------------------------" << std::endl;
		Real OptionPrice = europeanOption.NPV();
		std::cout << "OptionPrice = europeanOption.NPV()=" << OptionPrice << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "MCEuropeanEngine with GeneralizedBlackScholesProcess" <<std::endl ;

        europeanOption.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new MCEuropeanEngine<PseudoRandom>(
					bsProcess, 10,
					Null<Size>(),
					true,
					false,
					10000,
					Null<Real>(),
					Null<Size>(), SeedGenerator::instance().get()
					))
			);
//Time Calcul
        clock_t tStart = clock();
		std::cout<<"Option Price " << europeanOption.NPV() << std::endl;
		printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
		std::cout <<"Error Estimation "<< europeanOption.errorEstimate() << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "MCEuropeanEngine with constantBlackScholesModel" << std::endl;
		europeanOption_2.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new MCEuropeanEngine_2<PseudoRandom>(
					bsProcess, 10,
					Null<Size>(),
					true,
					false,
					10000,
					Null<Real>(),
					Null<Size>(), SeedGenerator::instance().get()
					))
			);
		clock_t tStart_2 = clock();
		std::cout << "Option Price " << europeanOption_2.NPV() << std::endl;
		printf("Time taken: %.2fs\n", (double)(clock() - tStart_2) / CLOCKS_PER_SEC);
		std::cout << "Error Estimation " << europeanOption_2.errorEstimate() << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		system("pause");
return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
 }

