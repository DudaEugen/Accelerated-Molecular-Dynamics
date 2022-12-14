#include "Potential/PairPotential/APairPotential.hpp"

md::APairPotential::APairPotential(element first, element second,  IBaseFunction* function, double cutRadius) noexcept
	: elements{first, second}, function{function}, cutRadius{cutRadius}
{
}

double md::APairPotential::energy(double distance) const
{
	return function->function(distance);
}

double md::APairPotential::derivative(double distance) const
{
	return function->derivative(distance);
}

bool md::APairPotential::isCorrectElements(const md::AtomPair& atomPair) const noexcept
{
	return (
		(
			atomPair.getFirst().chemElement == elements.first &&
			atomPair.getSecond().chemElement == elements.second
		) || (
			atomPair.getFirst().chemElement == elements.second &&
			atomPair.getSecond().chemElement == elements.first
		)
	);
}


void md::APairPotential::addAccelerations(md::NeighboursList& neighboursList) const
{
	for (auto& atomPair: neighboursList.getPairs())
	{
		double distance = atomPair.getDistance();
		if (distance < getCutRadius() && isCorrectElements(atomPair))
		{
			Vector force = derivative(atomPair.getDistance()) *
							atomPair.getProjections()/atomPair.getDistance();

			atomPair.getFirst().addAcceleration(force / atomPair.getFirst().mass);
			atomPair.getSecond().addAcceleration(-force / atomPair.getSecond().mass);
		}
	}
}

double md::APairPotential::getCutRadius() const noexcept
{
	return cutRadius;
}

md::APairPotential::~APairPotential()
{
	delete function;
}
