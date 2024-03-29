#include "Potential/PairPotential/MorsePotential.hpp"
#include <cmath>

md::MorsePotential::MorsePotential(element first, element second, double De, double re, double a, double cutRadius)
	: APairPotential{first, second, cutRadius}, De{De}, re{re}, a{a}
{
}

md::MorsePotential::MorsePotential(element el, double De, double re, double a, double cutRadius)
	: MorsePotential{el, el, De, re, a, cutRadius}
{
}

md::MorsePotential::~MorsePotential() {}

md::Vector md::MorsePotential::computeForce(const AtomPair& pair) const
{
	double distance = pair.getDistance();
	return 2 * De * a * 
		(std::exp(-a*(distance - re)) - std::exp(-2*a* (distance - re))) / distance * 
		pair.getProjections();
}
