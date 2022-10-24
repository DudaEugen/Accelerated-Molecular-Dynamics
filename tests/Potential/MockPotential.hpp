#pragma once
#ifndef TAHD_MOCK_POTENTIAL_H
#define TAHD_MOCK_POTENTIAL_H

#include "Potential/APotential.hpp"

class MockPotential: public md::APotential
{
    double cutR;
protected:
    void computeAndSetAccelerations(md::NeighboursList& neighboursList) const override;
public:
    MockPotential(double cutRadius);
    ~MockPotential() override;
	double getCutRadius() const noexcept override;
};

#endif  //TAHD_MOCK_POTENTIAL_H
