#pragma once
#ifndef TAHD_MOCK_POTENTIAL_H
#define TAHD_MOCK_POTENTIAL_H

#include "../Potential/APotential.h"

class MockPotential: public APotential
{
    double cutR;
public:
    MockPotential(const double cutRadius);
    ~MockPotential() override;
    void computeAndSetAccelerations() override;
	double getCutRadius() const noexcept override;
};

#endif  //TAHD_MOCK_POTENTIAL_H
