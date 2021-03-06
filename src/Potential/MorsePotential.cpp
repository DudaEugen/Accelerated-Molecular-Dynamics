#include "Potential/MorsePotential.hpp"
#include <cmath>
#include "Zip.hpp"

md::MorsePotential::MorsePotential(std::vector<AtomPair>* atomPairs, const std::size_t maxAtomPairTypes)
: APairPotential{ atomPairs, maxAtomPairTypes }
{
}

md::MorsePotential::~MorsePotential() {}

void md::MorsePotential::addPairType(element first, element second, 
		double dissociationEnergy, double equilibriumBondDistance, double a, double cutRadius)
{
	if (APairPotential::addPairType(first, second))
	{
		De.push_back(dissociationEnergy);
		re.push_back(equilibriumBondDistance);
		this->a.push_back(a);
		rc.push_back(cutRadius);
	}
}

void md::MorsePotential::computeAndSetAccelerations()
{
	Vector force;
	const std::vector<AtomPair>& atomPairs = *pairs;
	for (auto [atomPair, cutRadius, D_e, alpha]: 
		 utils::zip::Zip(atomPairs, std::as_const(rc), std::as_const(De), std::as_const(a)))
	{
		double distance = atomPair.getDistance();
		if (distance < cutRadius)
		{
			force = 2 * kElementaryCharge * 0.0001 * D_e * alpha * 
				( exp(-alpha*(distance - cutRadius)) - exp(-2*alpha* (distance - cutRadius)) ) / distance * 
				atomPair.getDistanceProjections();

			atomPair.getFirst().addAcceleration(force / atomPair.getFirst().mass);
			if (atomPair.getIsAtomsFromSameStream())
				atomPair.getSecond().addAcceleration(-force / atomPair.getSecond().mass);
		}
	}
}
