#include "Potential/MorsePotential.hpp"
#include <cmath>

MorsePotential::MorsePotential(std::vector<AtomPair>* atomPairs, const std::size_t maxAtomPairTypes)
: APairPotential{ atomPairs, maxAtomPairTypes }
{
}

MorsePotential::~MorsePotential() {}

void MorsePotential::addPairType(element first, element second, double dissociationEnergy, double equilibriumBondDistance, double a, double cutRadius)
{
	if (APairPotential::addPairType(first, second))
	{
		De.push_back(dissociationEnergy);
		re.push_back(equilibriumBondDistance);
		this->a.push_back(a);
		rc.push_back(cutRadius);
	}
}

void MorsePotential::computeAndSetAccelerations()
{
	Vector force;
	std::vector<AtomPair>& atomPairs = *pairs;
	for (std::size_t index = 0; index < atomPairs.size(); ++index)
	{
		double distance = atomPairs[index].getDistance();
		if (distance < rc[index])
		{
			force = 2 * Q_ELEMENTARY * 0.0001 * De[index] * a[index] * 
				( exp(-a[index]*(distance - re[index])) - exp(-2*a[index] * (distance - re[index])) ) / distance * 
				atomPairs[index].getDistanceProjections();

			atomPairs[index].getFirst().addAcceleration(force / atomPairs[index].getFirst().mass);
			if (atomPairs[index].getIsAtomsFromSameStream())
				atomPairs[index].getSecond().addAcceleration(-force / atomPairs[index].getSecond().mass);
		}
	}
}
