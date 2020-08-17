#pragma once
#ifndef TAHD_ABSTRACT_POTENTIAL_H
#define TAHD_ABSTRACT_POTENTIAL_H

#include <vector>
#include "../AtomPair.h"

class APotential
{
protected:
	std::vector<AtomPair>* pairs;
public:
	APotential(std::vector<AtomPair>* atomPairs) noexcept;
	virtual ~APotential() = default;
	virtual void computeAndSetAccelerations() = 0;
	virtual double getCutRadius() const noexcept = 0;
};

#endif	//TAHD_ABSTRACT_POTENTIAL_H
