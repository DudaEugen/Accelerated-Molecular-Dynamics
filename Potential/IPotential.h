#pragma once
#ifndef TAHD_INTERFACE_POTENTIAL_H
#define TAHD_INTERFACE_POTENTIAL_H

#include <vector>
#include "../AtomPair.h"

class IPotential
{
public:
	virtual ~IPotential() = default;
	virtual void computeAndSetAccelerations() = 0;
	virtual double getCutRadius() const = 0;
};

#endif	//TAHD_INTERFACE_POTENTIAL_H
