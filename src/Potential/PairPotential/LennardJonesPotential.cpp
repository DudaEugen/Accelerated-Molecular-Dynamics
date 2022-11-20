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


double md::LennardJonesPotential::derivative(const AtomPair& pair) const
{
	double distance = pair.getDistance();
	return 24*eps*(1 - 2*std::pow(rm/distance, 6)) * std::pow(rm / distance, 7) / rm;
}
