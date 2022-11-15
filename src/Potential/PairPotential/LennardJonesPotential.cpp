#include "Potential/PairPotential/LennardJonesPotential.hpp"
#include <cmath>

md::LennardJonesPotential::LennardJonesPotential(element first, element second, double eps, double rm, double cutRadius)
	: APairPotential{first, second, cutRadius}, eps{eps}, rm{rm}
{
}

md::LennardJonesPotential::LennardJonesPotential(element el, double eps, double rm, double cutRadius)
	: APairPotential{el, el, cutRadius}, eps{eps}, rm{rm}
{
}

md::LennardJonesPotential::~LennardJonesPotential() {}


md::Vector md::LennardJonesPotential::computeForce(const AtomPair& pair) const
{
	double distance = pair.getDistance();
	return 24 * eps *
		(1 - 2*std::pow(rm/distance, 6)) * std::pow(rm / distance, 8) / std::pow(rm, 2) *
		pair.getProjections();
}
