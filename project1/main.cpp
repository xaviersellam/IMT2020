#include <iostream>
#include <cmath>
#include <algorithm>
#include "ConstantBSProcess.h"
#include "mceuropeanengine.hpp"
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/quantlib.hpp>

using namespace QuantLib;

int main(int argc, char **argv) {

double call = call_price(S, K, r, v, T);
double put = put_price(S, K, r, v, T);
ConstantBSProcess ConstantBSProcess1;
std::cout<<ConstantBSProcess1.drift()<<std::endl;

return 0;

}
