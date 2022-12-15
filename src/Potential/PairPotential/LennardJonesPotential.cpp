#include "Potential/PairPotential/LennardJonesPotential.hpp"

md::LennardJonesPotential::LennardJonesPotential(element first, element second, double eps, double rm, double cutRadius)
	: APairPotential{
		first,
		second,
		new md::Function(
			4*P0*utils::fcd::power<12>(P1/X) - 4*P0*utils::fcd::power<6>(P1/X),
			std::vector<double>{eps, rm}
		),
		cutRadius
	}
{
}

md::LennardJonesPotential::LennardJonesPotential(element el, double eps, double rm, double cutRadius)
	: LennardJonesPotential{el, el, eps, rm, cutRadius}
{
}

md::LennardJonesPotential::~LennardJonesPotential() {}
