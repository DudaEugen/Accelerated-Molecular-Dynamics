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

double md::LennardJonesPotential::energy(double distance) const
{
	double param = std::pow(rm/distance, 6);
	return 4*eps*param*(param - 1);
}

double md::LennardJonesPotential::derivative(double distance) const
{
	return 24*eps*(1 - 2*std::pow(rm/distance, 6)) * std::pow(rm / distance, 7) / rm;
}
