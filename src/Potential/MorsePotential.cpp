#include "Potential/MorsePotential.hpp"
#include <cmath>
#include "Zip.hpp"

md::MorsePotential::MorsePotential(element first, element second, double De, double re, double a, double cutRadius)
	: APairPotential{first, second, cutRadius}, De{De}, re{re}, a{a}
{
}

md::MorsePotential::MorsePotential(element el, double De, double re, double a, double cutRadius)
	: MorsePotential{el, el, De, re, a, cutRadius}
{
}

md::MorsePotential::~MorsePotential() {}

void md::MorsePotential::computeAndSetAccelerations(std::vector<AtomPair>& atomPairs) const
{
	for (auto& atomPair: atomPairs)
	{
		double distance = atomPair.getDistance();
		if (distance < cutRadius && isCorrectElements(atomPair))
		{
			Vector force = 2 * kElementaryCharge * 0.0001 * De * a * 
				( exp(-a*(distance - re)) - exp(-2*a* (distance - re)) ) / distance * 
				atomPair.getProjections();

			atomPair.getFirst().addAcceleration(force / atomPair.getFirst().mass);
			atomPair.getSecond().addAcceleration(-force / atomPair.getSecond().mass);
		}
	}
}
