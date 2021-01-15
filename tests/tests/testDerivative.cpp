#include "../tests.hpp"
#include "calculation of derivatives/functions.hpp"

using namespace utils;
namespace impl = fcd::implementation;

void staticTestsDerivative()
{
    double x = random<-3, 3>();
    std::vector<double> params = {random(), random()};

    static_assert(std::is_same_v<
		decltype(fcd::derivative(fcd::Parameter(0) * (fcd::Parameter(1) + x))), 
		fcd::implementation::ZeroConstanta
	>);
	static_assert(std::is_same_v<
		decltype(fcd::power<3>(fcd::sqRoot(fcd::exponenta(-2 * 5)))), 
		impl::Constanta
	>);
	static_assert(std::is_same_v<
		decltype(fcd::derivative<6>(fcd::Parameter(0) * fcd::power<5>(fcd::Variable()))), 
		fcd::implementation::ZeroConstanta
	>);
	static_assert(std::is_same_v<
		decltype(fcd::derivative(fcd::Variable() + 2*fcd::Variable())), 
		impl::Constanta
	>);
	static_assert(std::is_same_v<
		decltype(fcd::derivative<9>(x * fcd::power<8>(fcd::Variable()))), 
		fcd::implementation::ZeroConstanta
	>);
	static_assert(std::is_same_v<
		decltype(setParameters(x * fcd::root<5>(fcd::Parameter(0)), params)), 
		impl::Constanta
	>);
}

void testDerivativeFunctions()
{
    double x = random<-3, 3>();

    auto f = fcd::exponenta(fcd::Variable());
	assert(equal(f(x), exp(x)));
	assert(equal(fcd::derivative(f)(x), fcd::derivative<5>(f)(x)));

    auto f2 = 5*fcd::power<2>(fcd::Variable()) + fcd::Variable();
	assert(equal(f2(x), 5*x*x + x));
	assert(equal(fcd::derivative(f2)(x), 10*x + 1));
	assert(equal(fcd::derivative<2>(f2)(x), 10));
	assert(equal(fcd::derivative<3>(f2)(x), 0));

    auto f4 = -0.5*fcd::power<-2>(fcd::Variable());
	assert(equal(fcd::derivative<2>(f4)(x), -3/(pow(x,4)), 10));

	auto f5 = fcd::sqRoot(fcd::Variable()) + fcd::power<2>(fcd::root<5>(fcd::Variable()));
	assert(equal(fcd::derivative(f5)(abs(x)), 1/(2*sqrt(abs(x))) + 0.4*pow(abs(x), -0.6), 10));

	assert(equal(fcd::root<3>(fcd::Variable())(x), fcd::cbRoot(fcd::Variable())(x), 10));
	assert(equal(fcd::derivative<3>(fcd::root<3>(fcd::Variable()))(x), fcd::derivative<3>(fcd::cbRoot(fcd::Variable()))(x), 10));

	assert(equal(fcd::cosinus(fcd::Variable())(x), fcd::sinus(fcd::Variable() + 1.57079632679489661923)(x), 10));
	assert(equal(fcd::derivative(fcd::sinus(fcd::Variable()))(x), fcd::cosinus(fcd::Variable())(x), 10));

	assert(equal(fcd::tangent(fcd::Variable())(x), sin(x) / cos(x), 10));
	assert(equal(fcd::derivative(fcd::tangent(fcd::Variable()))(x), pow(cos(x), -2), 10));

	assert(equal(fcd::logarithm(fcd::Variable())(abs(x)), log(abs(x)), 10));
	assert(equal(fcd::derivative(fcd::logarithm(fcd::Variable()))(abs(x)), 1/abs(x), 10));
	assert(equal(fcd::logarithm<2>(fcd::Variable())(abs(x)), log2(abs(x)), 10));
	assert(equal(fcd::logarithm<10>(fcd::Variable())(abs(x)), log10(abs(x)), 10));
	assert(equal(fcd::derivative(fcd::logarithm<3>(fcd::Variable()))(abs(x)), 1/(abs(x) * log(3)), 10));

	auto f6 = fcd::sqRoot(fcd::exponential<3>(-2 * fcd::Variable()));
	assert(equal(f6(x), pow(3, -x), 10));
	assert(equal(fcd::derivative<5>(f6)(x), -pow(3,-x) * pow(log(3), 5), 10));

    auto f8 = fcd::sinus(fcd::Variable())/fcd::cosinus(fcd::Variable());
	assert(equal(f8(x), fcd::tangent(fcd::Variable())(x), 10));
	assert(equal(fcd::derivative(f8)(x), pow(cos(x), -2), 10));

    auto f10 = fcd::power<3>(fcd::Variable()) - fcd::Variable() - 5;
	assert(equal(f10(x), pow(x, 3) - x - 5, 10));
	assert(equal(fcd::derivative<2>(f10)(x), 6*x, 10));
}

void testDerivativeWithParameters()
{
    double x = random<-3, 3>();	

	std::vector<double> params = {1, -2};
	auto f3_uncomplete = fcd::power<3>(fcd::Variable())*fcd::exponenta(fcd::Variable()) +
						 fcd::exponenta(fcd::Parameter(0))*fcd::Parameter(1);
	auto f3 = fcd::setParameters(f3_uncomplete, params);
	assert(equal(f3(x), x*x*x*exp(x) + params[1] * exp(params[0]), 10));
	assert(equal(fcd::derivative(f3)(x), 3*x*x*exp(x) + x*x*x*exp(x), 10));
	assert(equal(fcd::derivative<2>(f3)(x), fcd::derivative(f3)(x) + 6*x*exp(x) + 3*x*x*exp(x), 10));

	auto f7_uncomplete = fcd::Parameter(0) * fcd::cosinus(3*fcd::Variable() + fcd::Parameter(1));
	auto f7 = fcd::setParameters(f7_uncomplete, params);
	assert(equal(f7(x), params[0] * cos(3*x + params[1]), 10));
	assert(equal(fcd::derivative(f7)(x), -3*params[0] * sin(3*x + params[1]), 10));

	auto f9_uncomplete = fcd::Parameter(1) * fcd::exponenta(-fcd::Variable() / fcd::Parameter(0));
	auto f9 = fcd::setParameters(f9_uncomplete, params);
	assert(equal(f9(x), params[1]*exp(-x/params[0]), 10));
	assert(equal(fcd::derivative<3>(f9)(x), -params[1]/pow(params[0], 3)*exp(-x/params[0]), 10));
}

void testDerivative()
{
    staticTestsDerivative();
    testDerivativeFunctions();
    testDerivativeWithParameters();	
}
