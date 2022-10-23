#include <algorithm>
#include "Potential/APotential.hpp"

md::APotential::~APotential() = default;

void md::APotential::computeAndSetAccelerations(
    std::vector<AtomPair>& atomPairs,
    std::vector<Atom>& atoms
) const
{
    discardAccelerations(atoms);
    computeAndSetAccelerations(atomPairs);
}

void md::APotential::discardAccelerations(std::vector<Atom>& atoms) const
{
    std::for_each(atoms.begin(), atoms.end(), [](Atom& atom){ atom.setAcceleration(Vector{}); });
}
