#pragma once
#ifndef TAHD_ABSTRACT_POTENTIAL_H
#define TAHD_ABSTRACT_POTENTIAL_H

#include <vector>
#include "NeighboursList/NeighboursList.hpp"

namespace md
{
	class APotential
	{
	public:
		virtual ~APotential() = 0;
		virtual void addAccelerations(NeighboursList& neighboursList) const = 0;
		virtual double getCutRadius() const noexcept = 0;
	};
}

#endif	//TAHD_ABSTRACT_POTENTIAL_H
