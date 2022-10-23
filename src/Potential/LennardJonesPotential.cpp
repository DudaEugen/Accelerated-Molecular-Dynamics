#include "Potential/LennardJonesPotential.hpp"
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


void md::LennardJonesPotential::computeAndSetAccelerations(std::vector<AtomPair>& atomPairs) const
{
	for (auto& atomPair: atomPairs)
	{
		double distance = atomPair.getDistance();
		if (distance < cutRadius && isCorrectElements(atomPair))
		{
			Vector force = 24 * eps *
				( 1 - 2*pow(rm/distance, 6) ) * pow(rm / distance, 8) / std::pow(rm, 2) *
				atomPair.getProjections();

			atomPair.getFirst().addAcceleration(force / atomPair.getFirst().mass);
			atomPair.getSecond().addAcceleration(-force / atomPair.getSecond().mass);
		}
	}
}
