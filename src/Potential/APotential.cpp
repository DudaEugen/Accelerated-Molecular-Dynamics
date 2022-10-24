#include <algorithm>
#include "Potential/APotential.hpp"

md::APotential::~APotential() = default;

void md::APotential::computeAndSetAccelerations(
    NeighboursList& neighboursList,
    std::vector<Atom>& atoms
) const
{
    discardAccelerations(atoms);
    computeAndSetAccelerations(neighboursList);
}

void md::APotential::discardAccelerations(std::vector<Atom>& atoms) const
{
    std::for_each(atoms.begin(), atoms.end(), [](Atom& atom){ atom.setAcceleration(Vector{}); });
}
