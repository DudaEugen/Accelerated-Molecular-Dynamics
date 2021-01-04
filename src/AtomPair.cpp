#include "AtomPair.hpp"

md::AtomPair::AtomPair(Atom& first, Atom& second)  noexcept
	: atomPair{ &first, &second }
{
	computeDistance();
}

md::AtomPair::AtomPair(Atom& first, Atom& second, const double d, const Vector deltaCoordinates) noexcept
	: atomPair{ &first, &second }, distance{d}, dProjections{deltaCoordinates}
{
}

md::Atom& md::AtomPair::getAtomByIndex(const index i) const noexcept
{
	return *atomPair[static_cast<int>(i)];
}

md::Atom& md::AtomPair::getAtomWithAnotherIndex(const index i) const noexcept
{
	int ind = static_cast<int>(i) == 0 ? 1 : 0;
	return *atomPair[ind];
}

md::Atom& md::AtomPair::getFirst() const noexcept { return *atomPair[0]; }

md::Atom& md::AtomPair::getSecond() const noexcept { return *atomPair[1]; }

double md::AtomPair::getDistance() const noexcept { return distance; }

md::Vector::ConstPass md::AtomPair::getDistanceProjections() const noexcept 
{ 
	return dProjections; 
}

bool md::AtomPair::getIsAtomsFromSameStream() const noexcept { return isAtomsFromSameStream; }

void md::AtomPair::setIsAtomsFromSameStream(const bool isSame) noexcept
{ 
	isAtomsFromSameStream = isSame; 
}

double md::AtomPair::computeDistance() noexcept
{
	dProjections = atomPair[1]->getCoordinates() - atomPair[0]->getCoordinates();
	distance = dProjections.absoluteValue();
	return distance;
}

double md::AtomPair::computeDistance(const BorderConditions& borderConditions) noexcept
{
	dProjections = atomPair[1]->getCoordinates() - atomPair[0]->getCoordinates();
	distance = borderConditions(dProjections);
	return distance;
}
