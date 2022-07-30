#pragma once
#ifndef TAHD_MOCK_POTENTIAL_H
#define TAHD_MOCK_POTENTIAL_H

#include "Potential/IPotential.hpp"

class MockPotential: public md::IPotential
{
    double cutR;
public:
    MockPotential(double cutRadius);
    ~MockPotential() override;
    void computeAndSetAccelerations(std::vector<md::AtomPair>& atomPairs) const override;
	double getCutRadius() const noexcept override;
};

#endif  //TAHD_MOCK_POTENTIAL_H
