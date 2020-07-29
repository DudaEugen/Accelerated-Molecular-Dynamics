#pragma once
#ifndef TAHD_ABSTRACT_POTENTIAL_H
#define TAHD_ABSTRACT_POTENTIAL_H

#include <vector>
#include "../AtomicSystem.h"

class APotential
{
protected:
	AtomicSystem* system;
public:
	APotential(AtomicSystem* s) noexcept;
	virtual ~APotential() = default;
	virtual void computeAndSetAccelerations() = 0;
	virtual double getCutRadius() const noexcept = 0;
};

#endif	//TAHD_ABSTRACT_POTENTIAL_H
