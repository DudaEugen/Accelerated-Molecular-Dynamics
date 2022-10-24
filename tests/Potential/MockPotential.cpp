#include "Potential/MockPotential.hpp"

MockPotential::MockPotential(double cutRadius)
    : APotential{}, cutR{ cutRadius }
{
}

MockPotential::~MockPotential() {}

void MockPotential::computeAndSetAccelerations(md::NeighboursList& neighboursList) const { return; }

double MockPotential::getCutRadius() const noexcept { return cutR; }
