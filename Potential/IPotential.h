#pragma once
#ifndef TAHD_IPOTENTIAL_H
#define TAHD_IPOTENTIAL_H

#include <vector>
#include "../AtomPair.h"

class IPotential
{
public:
	virtual ~IPotential() = default;
	virtual void computeAndSetAccelerations(const std::vector<AtomPair>& pairs) = 0;
	virtual double getCutRadius() const = 0;
};

#endif	//TAHD_IPOTENTIAL_H
