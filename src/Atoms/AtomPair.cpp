#include "Atoms/AtomPair.hpp"
#include <tuple>

md::AtomPair::AtomPair(Atom& first, Atom& second)  noexcept
	: firstAtom{ first }, secondAtom { second }
{
	computeDistanceWithProjections();
}

md::Atom& md::AtomPair::getFirst() const noexcept { return firstAtom; }

md::Atom& md::AtomPair::getSecond() const noexcept { return secondAtom; }

double md::AtomPair::getDistance() const noexcept { return distance; }

md::Vector md::AtomPair::getProjections() const noexcept { return dProjections; }

std::pair<double, md::Vector::ConstPass> md::AtomPair::getDistanceWithProjections() const noexcept 
{ 
	return std::pair(distance, dProjections); 
}

std::pair<double, md::Vector::ConstPass> md::AtomPair::computeDistanceWithProjections()
{
	Position::ConstPass first = firstAtom.getPosition();
	Position::ConstPass second = secondAtom.getPosition();
	std::tie(distance, dProjections) = second.distanceWithProjectionsTo(first);
	return getDistanceWithProjections();
}
