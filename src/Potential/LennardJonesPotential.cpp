#include "Potential/LennardJonesPotential.hpp"
#include <cmath>

LennardJonesPotential::LennardJonesPotential(std::vector<AtomPair>* atomPairs, const std::size_t maxAtomPairTypes)
	: APairPotential{ atomPairs, maxAtomPairTypes }
{
}

LennardJonesPotential::~LennardJonesPotential() {}

void LennardJonesPotential::addPairType(element first, element second, double bondEnergy, double bondRadius, double cutRadius)
{
	if (APairPotential::addPairType(first, second))
	{
		eps.push_back(bondEnergy);
		rm.push_back(bondRadius);
		rc.push_back(cutRadius);
	}
}

void LennardJonesPotential::computeAndSetAccelerations()
{
	Vector force;
	std::vector<AtomPair>& atomPairs = *pairs;
	for (std::size_t i = 0; i < atomPairs.size(); ++i)
	{
		double distance = atomPairs[i].getDistance();
		if (distance < rc[i])
		{
			force = 24 * Q_ELEMENTARY * 0.0001 * eps[i] *
				( 1 - 2*pow(rm[i]/distance, 6) ) * pow(rm[i] / distance, 8) / std::pow(rm[i], 2) *
				atomPairs[i].getDistanceProjections();

			atomPairs[i].getFirst().addAcceleration(force / atomPairs[i].getFirst().mass);
			if (atomPairs[i].getIsAtomsFromSameStream())
				atomPairs[i].getSecond().addAcceleration(-force / atomPairs[i].getSecond().mass);
		}
	}
}
