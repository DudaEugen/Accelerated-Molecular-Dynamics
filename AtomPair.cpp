#include "AtomPair.h"

BorderConditions* AtomPair::borderConditions = nullptr;

AtomPair::AtomPair(Atom* first, Atom* second, const bool isUsingBorderConditions) : atomPair{ first, second }, isUsingBorderConditions{ isUsingBorderConditions }
{
	computeDistance();
}

AtomPair::AtomPair(Atom* first, Atom* second, const double d, const Vector deltaCoordinates, const bool isUsingBorderConditions)
	: atomPair{ first, second }, distance{d}, dProjections{deltaCoordinates}, isUsingBorderConditions{ isUsingBorderConditions }
{
}

void AtomPair::setBorderConditions(BorderConditions* borderConditions) { AtomPair::borderConditions = borderConditions; }

Atom& AtomPair::getFirst() const { return *atomPair[0]; }

Atom& AtomPair::getSecond() const { return *atomPair[1]; }

double AtomPair::getDistance() const { return distance; }

Vector::ConstVectorPass AtomPair::getDistanceProjections() const { return dProjections; }

bool AtomPair::getIsAtomsFromSameStream() const { return isAtomsFromSameStream; }

void AtomPair::setIsUsingBorderConditions(const bool isUsing) { isUsingBorderConditions = isUsing; }

void AtomPair::setIsAtomsFromSameStream(const bool isSame) { isAtomsFromSameStream = isSame; }

double AtomPair::computeDistance()
{
	dProjections = atomPair[0]->getCoordinates() - atomPair[1]->getCoordinates();
	if (isUsingBorderConditions)
		distance = borderConditions->operator()(dProjections);
	else
		distance = dProjections.absoluteValue();
	return distance;
}
