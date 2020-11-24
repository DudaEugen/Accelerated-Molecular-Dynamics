#include "Potential/LennardJonesPotential.hpp"
#include <cmath>
#include "utility/Zip.hpp"

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
	const std::vector<AtomPair>& atomPairs = *pairs;
	for (auto [atomPair, cutRadius, e, r_m]: Zip(atomPairs, std::as_const(rc), std::as_const(eps), std::as_const(rm)))
	{
		double distance = atomPair.getDistance();
		if (distance < cutRadius)
		{
			force = 24 * Q_ELEMENTARY * 0.0001 * e *
				( 1 - 2*pow(r_m/distance, 6) ) * pow(r_m / distance, 8) / std::pow(r_m, 2) *
				atomPair.getDistanceProjections();

			atomPair.getFirst().addAcceleration(force / atomPair.getFirst().mass);
			if (atomPair.getIsAtomsFromSameStream())
				atomPair.getSecond().addAcceleration(-force / atomPair.getSecond().mass);
		}
	}
}
