#include "AtomPair.h"

BorderConditions* AtomPair::borderConditions = nullptr;

AtomPair::AtomPair(Atom* first, Atom* second, const bool isUsingBorderConditions) : atomPair{ first, second }, isUsingBorderConditions{ isUsingBorderConditions }
{
	computeDistance();
}

AtomPair::AtomPair(Atom* first, Atom* second, const double d, const ProjectionTuple& deltaCoordinate, const bool isUsingBorderConditions)
	: atomPair{ first, second }, distance{d}, dProjections{deltaCoordinate}, isUsingBorderConditions{ isUsingBorderConditions }
{
}

void AtomPair::setBorderConditions(BorderConditions* borderConditions)
{
	AtomPair::borderConditions = borderConditions;
}

void AtomPair::computeDistance_ignoringBorderConditions()
{
	dProjections = atomPair[0]->getCoordinates() - atomPair[1]->getCoordinates();
	distance = dProjections.absoluteValue();
}

void AtomPair::computeDistance_usingBorderConditions()
{
	dProjections = atomPair[0]->getCoordinates() - atomPair[1]->getCoordinates();
	distance = borderConditions->computeDistance(dProjections);
}

void AtomPair::computeDistance()
{
	isUsingBorderConditions ? computeDistance_usingBorderConditions() : computeDistance_ignoringBorderConditions();
}

double AtomPair::computeDistance(const Atom* first, const Atom* second, const bool isUsingBorderConditions)
{
	ProjectionTuple projections = first->getCoordinates() - second->getCoordinates();
	return isUsingBorderConditions ? borderConditions->computeDistance(projections) : projections.absoluteValue();
}

double AtomPair::computeDistance(const Atom* first, const Atom* second, ProjectionTuple& projections, const bool isUsingBorderConditions)
{
	projections = first->getCoordinates() - second->getCoordinates();
	return isUsingBorderConditions ? borderConditions->computeDistance(projections) : projections.absoluteValue();
}
