#pragma once
#ifndef TAHD_ABSTRACT_POTENTIAL_H
#define TAHD_ABSTRACT_POTENTIAL_H

#include <vector>
#include "Atoms/AtomPair.hpp"

namespace md
{
	class IPotential
	{
	public:
		virtual ~IPotential() = 0;
		virtual void computeAndSetAccelerations(std::vector<AtomPair>& atomPairs) const = 0;
		virtual double getCutRadius() const noexcept = 0;
	};
}

#endif	//TAHD_ABSTRACT_POTENTIAL_H
