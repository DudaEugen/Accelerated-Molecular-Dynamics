#include "Potential/MockPotential.hpp"

MockPotential::MockPotential(double cutRadius)
    : APotential{}, cutR{ cutRadius }
{
}

MockPotential::~MockPotential() {}

void MockPotential::computeAndSetAccelerations(std::vector<md::AtomPair>& atomPairs) const { return; }

double MockPotential::getCutRadius() const noexcept { return cutR; }
