#include "Potential/APairPotential.hpp"

md::APairPotential::APairPotential(element first, element second, double cutRadius) noexcept
	: elements{first, second}, cutRadius{cutRadius}
{
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

double md::APairPotential::getCutRadius() const noexcept
{
	return cutRadius;
}
