#include "MorsePotential.h"

MorsePotential::MorsePotential(double dissociationEnergy, double equilibriumBondDistance, double a, double cutRadius)
: De{  dissociationEnergy }, re{ equilibriumBondDistance }, a{ a }, rc{ cutRadius }
{
}

MorsePotential::~MorsePotential() {}

void MorsePotential::computeAndSetAccelerations(const std::vector<AtomPair>& pairs)
{
	Vector acceleration;
	for (const AtomPair& pair: pairs)
	{
		double distance = pair.getDistance();
		if (distance < rc)
		{
			acceleration = 2 * Q_ELEMENTARY * 0.0001 * De * a * (exp(-a * (distance - re)) - exp(-2 * a * (distance - re))) / distance * pair.getDistanceProjections();

			pair.getFirst().addAcceleration(acceleration / pair.getFirst().mass);
			if (pair.getIsAtomsFromSameStream())
				pair.getSecond().addAcceleration(-acceleration / pair.getSecond().mass);
		}
	}
}

double MorsePotential::getCutRadius() const { return rc; }
