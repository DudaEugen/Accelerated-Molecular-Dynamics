#include "AtomPair.hpp"

AtomPair::AtomPair(Atom& first, Atom& second)  noexcept
	: atomPair{ &first, &second }
{
	computeDistance();
}

AtomPair::AtomPair(Atom& first, Atom& second, const double d, const Vector deltaCoordinates) noexcept
	: atomPair{ &first, &second }, distance{d}, dProjections{deltaCoordinates}
{
}

Atom& AtomPair::getAtomByIndex(const index i) const noexcept
{
	return *atomPair[static_cast<int>(i)];
}

Atom& AtomPair::getAtomWithAnotherIndex(const index i) const noexcept
{
	int ind = static_cast<int>(i) == 0 ? 1 : 0;
	return *atomPair[ind];
}

Atom& AtomPair::getFirst() const noexcept { return *atomPair[0]; }

Atom& AtomPair::getSecond() const noexcept { return *atomPair[1]; }

double AtomPair::getDistance() const noexcept { return distance; }

Vector::ConstVectorPass AtomPair::getDistanceProjections() const noexcept 
{ 
	return dProjections; 
}

bool AtomPair::getIsAtomsFromSameStream() const noexcept { return isAtomsFromSameStream; }

void AtomPair::setIsAtomsFromSameStream(const bool isSame) noexcept
{ 
	isAtomsFromSameStream = isSame; 
}

double AtomPair::computeDistance() noexcept
{
	dProjections = atomPair[1]->getCoordinates() - atomPair[0]->getCoordinates();
	distance = dProjections.absoluteValue();
	return distance;
}

double AtomPair::computeDistance(const BorderConditions& borderConditions) noexcept
{
	dProjections = atomPair[1]->getCoordinates() - atomPair[0]->getCoordinates();
	distance = borderConditions(dProjections);
	return distance;
}
