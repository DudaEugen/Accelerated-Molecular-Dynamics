#include "MockPotential.hpp"

MockPotential::MockPotential(const double cutRadius)
    : APotential{ nullptr }, cutR{ cutRadius }
{
}

MockPotential::~MockPotential() {}

void MockPotential::computeAndSetAccelerations() { return; }

double MockPotential::getCutRadius() const noexcept { return cutR; }
