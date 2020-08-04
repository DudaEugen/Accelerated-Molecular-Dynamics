#include "AtomPair.h"

BorderConditions* AtomPair::borderConditions = nullptr;

AtomPair::AtomPair(Atom* first, Atom* second, const bool isUsingBorderConditions)  noexcept
	: atomPair{ first, second }, isUsingBorderConditions{ isUsingBorderConditions }
{
	computeDistance();
}

AtomPair::AtomPair(Atom* first, Atom* second, const double d, const Vector deltaCoordinates, const bool isUsingBorderConditions) noexcept
	: atomPair{ first, second }, distance{d}, dProjections{deltaCoordinates}, isUsingBorderConditions{ isUsingBorderConditions }
{
}

void AtomPair::setBorderConditions(BorderConditions* borderConditions) noexcept 
{ 
	AtomPair::borderConditions = borderConditions; 
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

void AtomPair::setIsUsingBorderConditions(const bool isUsing) noexcept 
{ 
	isUsingBorderConditions = isUsing; 
}

void AtomPair::setIsAtomsFromSameStream(const bool isSame) noexcept
{ 
	isAtomsFromSameStream = isSame; 
}

double AtomPair::computeDistance() noexcept
{
	dProjections = atomPair[0]->getCoordinates() - atomPair[1]->getCoordinates();
	if (isUsingBorderConditions)
		distance = borderConditions->operator()(dProjections);
	else
		distance = dProjections.absoluteValue();
	return distance;
}
