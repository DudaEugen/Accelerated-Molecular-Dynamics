#include "Potential/MorsePotential.hpp"
#include <cmath>
#include "Zip.hpp"

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
	const std::vector<AtomPair>& atomPairs = *pairs;
	for (auto [atomPair, cutRadius, D_e, alpha]: 
		 utils::zip::Zip(atomPairs, std::as_const(rc), std::as_const(De), std::as_const(a)))
	{
		double distance = atomPair.getDistance();
		if (distance < cutRadius)
		{
			force = 2 * Q_ELEMENTARY * 0.0001 * D_e * alpha * 
				( exp(-alpha*(distance - cutRadius)) - exp(-2*alpha* (distance - cutRadius)) ) / distance * 
				atomPair.getDistanceProjections();

			atomPair.getFirst().addAcceleration(force / atomPair.getFirst().mass);
			if (atomPair.getIsAtomsFromSameStream())
				atomPair.getSecond().addAcceleration(-force / atomPair.getSecond().mass);
		}
	}
}
