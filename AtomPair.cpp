#include "AtomPair.h"

AtomPair::AtomPair(Atom* first, Atom* second) : atomPair{ first, second }
{
	computeDistance();
}

AtomPair::AtomPair(Atom* first, Atom* second, const double d, const ProjectionTuple& deltaCoordinate)
	: atomPair{ first, second }, distance{d}, dProjections{deltaCoordinate}
{
}

void AtomPair::computeDistance()
{
	dProjections = atomPair[0]->getCoordinates() - atomPair[1]->getCoordinates();
	distance = dProjections.absoluteValue();
}

double AtomPair::computeDistance(const Atom* first, const Atom* second)
{
	ProjectionTuple projections = first->getCoordinates() - second->getCoordinates();
	return projections.absoluteValue();
}

double AtomPair::computeDistance(const Atom* first, const Atom* second, ProjectionTuple& projections)
{
	projections = first->getCoordinates() - second->getCoordinates();
	return projections.absoluteValue();
}
