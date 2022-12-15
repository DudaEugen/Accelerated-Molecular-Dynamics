#include "Potential/PairPotential/MorsePotential.hpp"

md::MorsePotential::MorsePotential(element first, element second, double De, double re, double a, double cutRadius)
	: APairPotential{
		first,
		second,
		new md::Function(
			P0*utils::fcd::power<2>(1 - utils::fcd::exponenta(-P1*X + P1*P2)),
			std::vector<double>{De, a, re}
		),
		cutRadius
	}
{
}

md::MorsePotential::MorsePotential(element el, double De, double re, double a, double cutRadius)
	: MorsePotential{el, el, De, re, a, cutRadius}
{
}

md::MorsePotential::~MorsePotential() {}
